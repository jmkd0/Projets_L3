#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include "mymc.h"

/* g++ -std=c++11 s1.cpp */

int main(int _ac, char** _av) {
  srand(1);
  chess_board_t C;
  C.init_silverman_4x5();
  C.print_board_with_color();
  return 0;
}
