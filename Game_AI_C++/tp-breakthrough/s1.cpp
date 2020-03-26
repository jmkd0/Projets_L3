#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include "mybt.h"
#include "monte_carlo.h"

/* g++ -std=c++11 s1.cpp */

int main_simple_random_query(int _ac, char** _av) {
  srand(1);
  bt_t N;
  N.init(6,6);
  N.print_board();
  bt_move_t m = N.get_rand_move();
  printf("\n");
  printf("m (%d %d %d %d)\n", m.line_i, m.col_i, m.line_f, m.col_f);
  N.play(m);
  N.print_board();
  return 0;
}
int main_simple_playout(int _ac, char** _av) {
  srand(4);
  bt_t N;
  N.init(6,6);
  N.print_board();
  N.playout(1);
  printf("score (BLACK) : %f\n", N.score(BLACK) );
  return 0;
}
//resolution avec random
int main_random(int _ac, char** _av) {
  srand(time(NULL));
  bt_t N;
  N.init(6,6);
  N.print_board();
  N.playout_random(1);
  printf("score (BLACK) : %f\n", N.score(BLACK) );
  return 0;
}
//resolution avec Monte Carlo
int main_monte_carlo(int _ac, char** _av) {
  srand(time(NULL));
  int nb_playout=100000;
  bt_t N;
  N.init(6,6);
  N.print_board();
  N.monte_carlo(1, nb_playout);
  printf("score (BLACK) : %f\n", N.score(BLACK) );
  return 0;
}
//resolution avec Monte Carlo Tree Search
int main_monte_carlo_tree_search(int _ac, char** _av) {
  srand(time(NULL));
  bt_t N;
  N.init(6,6);
  N.print_board();
  N.monte_carlo_tree_search(1);
  printf("score (BLACK) : %f\n", N.score(BLACK) );
  return 0;
}
//resolution avec Nested Monte Carlo Search (NMCS)
int main_NMCS(int _ac, char** _av) {
  srand(time(NULL));
  int LEVEL_MAX = 4;
  bt_t N;
  N.init(6,6);
  N.print_board();
  N.nested_monte_carlo(1, LEVEL_MAX);
  printf("score (BLACK) : %f\n", N.score(BLACK) );
  return 0;
}
int main(int _ac, char** _av) {
  //main_simple_random_query(_ac, _av);
  //main_simple_playout(_ac, _av);
  main_random (_ac, _av);
  //main_monte_carlo (_ac, _av);
  //main_monte_carlo_tree_search (_ac, _av);
  return 0;
}

