#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include "mybt.h"

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
int main(int _ac, char** _av) {
  //main_simple_random_query(_ac, _av);
  main_simple_playout(_ac, _av);
  return 0;
}

