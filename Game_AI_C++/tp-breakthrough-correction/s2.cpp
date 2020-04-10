#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include <sys/time.h>
#include "mybt.h"
#include "mctsbt.h"

/* g++ -std=c++11 s1.cpp */

// joue un playout
int main_simple_playout(int _ac, char** _av) {
  srand(4);
  bt_t N;
  N.init(6,6);
  N.print_board();
  N.playout(1);
  printf("score (WHITE) : %f\n", N.score(WHITE) );
  printf("score (BLACK) : %f\n", N.score(BLACK) );
  return 0;
}
// affiche une board et un coup possible
int main_simple_random_query(int _ac, char** _av) {
  srand(1);
  bt_t N;
  N.init(6,6);
  N.print_board();
  bt_move_t m = N.get_rand_move();
  printf("m (%d %d %d %d)\n", m.line_i, m.col_i, m.line_f, m.col_f);
  return 0;
}
// realise nb_iterations d'une recherche MCTS
// affiche les valeurs Wi/Ni des fils du noeud root 
// affiche le meilleur coup nommé "m"
int main_simple_query_MCTS(int _ac, char** _av) {
  srand(1);
  bt_t N;
  N.init(6,6);
  N.print_board();
  int nb_iterations = 1000;
  int max_depth = 1000;
  bt_tree_t T (nb_iterations, max_depth, N, WHITE);
  bt_move_t m = T.MCTS_UCT(2, nb_iterations);
  T.print(0);
  printf("m (%d %d %d %d)\n", m.line_i, m.col_i, m.line_f, m.col_f);
  return 0;
}
// des matchs de MC contre random
int main_match_MC_vs_random(int _ac, char** _av) {
  srand(1);
  int nb_iterations = 100;
  int nb_match = 10; 
  bt_t N;
  int rand_win = 0;
  int MC_win = 0;
  bool print_games = false;
  bool MC_play_first = false;
  for(int i = 0; i < nb_match; i++) {
    N.init(6,6);
    if(print_games) N.print_board();
    while(N.terminal() == EMPTY) {
      if(MC_play_first) {
	bt_MC_t T (N, WHITE);
	bt_move_t m = T.MC(i, nb_iterations);
	if(print_games) { printf("mc : "); m.print(); }
	N.play(m);
	if(print_games)	N.print_board();
	if(N.terminal() != EMPTY) { MC_win++; break; }
      } else {
	bt_move_t m = N.get_rand_move();
	if(print_games) { printf("rand : "); m.print(); }
	N.play(m);
	if(print_games) N.print_board();
	if(N.terminal() != EMPTY) { rand_win++; break; }
      }
      if(MC_play_first) {
	bt_move_t m = N.get_rand_move();
	if(print_games) { printf("rand : "); m.print(); }
	N.play(m);
	if(print_games) N.print_board();
	if(N.terminal() != EMPTY) { rand_win++; break; }
      } else {
	bt_MC_t T (N, BLACK);
	bt_move_t m = T.MC(i, nb_iterations);
	if(print_games) { printf("mc : "); m.print(); }
	N.play(m);
	if(print_games)	N.print_board();
	if(N.terminal() != EMPTY) { MC_win++; break; }
      }
    }
    if(print_games) { printf("---\n"); N.print_board(); }
  }
  printf("rand_win: %d  MC_win: %d\n", rand_win, MC_win);
  return 0;
}
// des matchs de MCTS contre random
int main_match_MCTS_vs_random(int _ac, char** _av) {
  srand(1);
  int nb_iterations = 1000;
  int max_depth = 100;
  int nb_match = 10; 
  bt_t N;
  int rand_win = 0;
  int MCTS_win = 0;
  bool print_games = false;
  for(int i = 0; i < nb_match; i++) {
    N.init(6,6);
    if(print_games) N.print_board();
    while(N.terminal() == EMPTY) {
      {
	bt_move_t m = N.get_rand_move();
	if(print_games) { printf("rand : "); m.print(); }
	N.play(m);
	if(print_games) N.print_board();
      }
      if(N.terminal() != EMPTY) { rand_win++; break; }
      {
	bt_tree_t T (nb_iterations, max_depth, N, BLACK);
	bt_move_t m = T.MCTS_UCT(i, nb_iterations);
	if(print_games) { printf("mcts : "); m.print(); }
	N.play(m);
	if(print_games) N.print_board();
      }
      if(N.terminal() != EMPTY) { MCTS_win++; break; }
    }
    if(print_games) { printf("---\n"); N.print_board(); }
  }
  printf("rand_win: %d  MCTS_win: %d\n", rand_win, MCTS_win);
  return 0;
}
int main_match_MCTS_vs_MC(int _ac, char** _av) {
  srand(1);
  int nb_iterations = 1000;
  int max_depth = 1000;
  int nb_match = 5; 
  bt_t N;
  int MC_win = 0;
  int MCTS_win = 0;
  bool print_games = false;
  bool MCTS_play_first = true;
  struct timeval i_time;    
  struct timeval f_time;
  float sum_eval_time = 0.0;
  float sum_eval_time2 = 0.0;
  int nb_eval_time = 0;
  bool eval_time = true; // uniquement si MCTS play first
  for(int i = 0; i < nb_match; i++) {
    N.init(6,6);
    if(print_games) N.print_board();
    while(N.terminal() == EMPTY) {
      if(MCTS_play_first) {
	if(eval_time) { gettimeofday (&i_time, 0); }
	bt_tree_t T (nb_iterations, max_depth, N, WHITE);
	bt_move_t m = T.MCTS_UCT(i, nb_iterations);
	if(eval_time) {
	  gettimeofday (&f_time, 0);
	  float time = ((float)(f_time.tv_sec - i_time.tv_sec)) +
	    ((float)(f_time.tv_usec - i_time.tv_usec))/1000000.0;
	  sum_eval_time += time;
	  sum_eval_time2 += (time*time);
	  nb_eval_time++;
	}
	if(print_games) { printf("mcts : "); m.print(); }
	N.play(m);
	if(print_games)	N.print_board();
	if(N.terminal() != EMPTY) { MCTS_win++; break; }
      } else {
	bt_MC_t T (N, WHITE);
	bt_move_t m = T.MC(i, nb_iterations);
	if(print_games) { printf("mcts : "); m.print(); }
	N.play(m);
	if(print_games)	N.print_board();
	if(N.terminal() != EMPTY) { MC_win++; break; }
      }
      if(MCTS_play_first) {
	bt_MC_t T (N, BLACK);
	bt_move_t m = T.MC(i, nb_iterations);
	if(print_games) { printf("mcts : "); m.print(); }
	N.play(m);
	if(print_games)	N.print_board();
	if(N.terminal() != EMPTY) { MC_win++; break; }
      } else {
	bt_tree_t T (nb_iterations, max_depth, N, BLACK);
	bt_move_t m = T.MCTS_UCT(i, nb_iterations);
	if(print_games) { printf("mcts : "); m.print(); }
	N.play(m);
	if(print_games)	N.print_board();
	if(N.terminal() != EMPTY) { MCTS_win++; break; }
      }
    }
    if(print_games) { printf("---\n"); N.print_board(); }
  }
  printf("MC_win: %d  MCTS_win: %d\n", MC_win, MCTS_win);
  if(eval_time) {
    printf("pour %d playout\n", nb_iterations);
    float avg = sum_eval_time/nb_eval_time;
    float avg2 = sum_eval_time2/nb_eval_time;
    float stddev = sqrt(avg2 - (avg*avg));
    printf("eval_time %.3f [%.3f]\n", avg, stddev);
  }
  return 0;
}

int main(int _ac, char** _av) {
  //main_simple_playout(_ac, _av);
  //main_simple_random_query(_ac, _av);
  //main_simple_query_MCTS(_ac, _av);
  //main_match_MC_vs_random(_ac, _av);
  //main_match_MCTS_vs_random(_ac, _av);
  main_match_MCTS_vs_MC(_ac, _av);
  return 0;
}

