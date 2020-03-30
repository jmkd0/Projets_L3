#ifndef MYMC_H
#define MYMC_H
#include <cstdio>
#include <cstdlib>
#define WHITE_P 0 // pawn
#define BLACK_P 1
#define WHITE_R 2 // rook
#define BLACK_R 3
#define WHITE_N 4 // knight
#define BLACK_N 5
#define WHITE_B 6 // bishop
#define BLACK_B 7
#define WHITE_K 8 // king
#define BLACK_K 9
#define WHITE_Q 10 // queen
#define BLACK_Q 11
#define EMPTY   12 // empty

#define PAWN 0
#define ROOK 1
#define KNIGHT 2
#define BISHOP 3
#define KING 4
#define QUEEN 5

#define MAX_NB_MOVES 1000

char* cboard = (char*)"ox.";

struct chess_piece_t {
  int piece; int line; int col;
};
struct chess_move_t {
  int line_i; int col_i;
  int line_f; int col_f;
  void print() {
    printf("(move %d %d %d %d)\n", line_i, col_i, line_f, col_f);
  }			
};
bool is_black(int _piece) {
  if(_piece == EMPTY) return false;
  if(_piece&1==1) return true;
  return false;
}
bool is_white(int _piece) {
  if(_piece == EMPTY) return false;
  if(_piece&1==0) return true;
  return false;
}

#define MAX_LINES 8
#define MAX_COLS 8
struct chess_board_t {
  int nbl;
  int nbc;
  int board[MAX_LINES][MAX_COLS];
  int turn;

  chess_piece_t white_pieces[2*MAX_LINES];
  int nb_white_pieces;
  chess_piece_t black_pieces[2*MAX_LINES];
  int nb_black_pieces;
  chess_move_t moves[MAX_NB_MOVES];
  int nb_moves;
  int moves_update_turn;
  
  void init_silverman_4x5() {
    nbl=5;
    nbc=4;
    for(int i = 0; i < MAX_LINES; i++)
      for(int j = 0; j < MAX_COLS; j++)
	board[i][j] = EMPTY;
    board[0][0]=BLACK_R; board[1][0]=BLACK_P;
    board[0][1]=BLACK_Q; board[1][1]=BLACK_P;
    board[0][2]=BLACK_K; board[1][2]=BLACK_P;
    board[0][3]=BLACK_R; board[1][3]=BLACK_P;
    board[4][0]=WHITE_R; board[3][0]=WHITE_P;
    board[4][1]=WHITE_Q; board[3][1]=WHITE_P;
    board[4][2]=WHITE_K; board[3][2]=WHITE_P;
    board[4][3]=WHITE_R; board[3][3]=WHITE_P;
    init_pieces();
    //update_moves();  
  }
  void add_black_piece(int _piece, int _i, int _j) {
    black_pieces[nb_black_pieces].piece = _piece;
    black_pieces[nb_black_pieces].line = _i;
    black_pieces[nb_black_pieces].col = _j;
    nb_black_pieces++;
  }
  void add_white_piece(int _piece, int _i, int _j) {
    white_pieces[nb_white_pieces].piece = _piece;
    white_pieces[nb_white_pieces].line = _i;
    white_pieces[nb_white_pieces].col = _j;
    nb_white_pieces++;
  }
  void init_pieces() {
    nb_white_pieces = 0;
    nb_black_pieces = 0;
    for(int i = 0; i < nbl; i++)
      for(int j = 0; j < nbc; j++) {
	if(board[i][j] == BLACK_P) add_black_piece(PAWN, i, j);
	else if(board[i][j] == WHITE_P) add_white_piece(PAWN, i, j);
	else if(board[i][j] == BLACK_R) add_black_piece(ROOK, i, j);
	else if(board[i][j] == WHITE_R) add_white_piece(ROOK, i, j);
	else if(board[i][j] == BLACK_N) add_black_piece(KNIGHT, i, j);
	else if(board[i][j] == WHITE_N) add_white_piece(KNIGHT, i, j);
	else if(board[i][j] == BLACK_B) add_black_piece(BISHOP, i, j);
	else if(board[i][j] == WHITE_B) add_white_piece(BISHOP, i, j);
	else if(board[i][j] == BLACK_K) add_black_piece(KING, i, j);
	else if(board[i][j] == WHITE_K) add_white_piece(KING, i, j);
	else if(board[i][j] == BLACK_Q) add_black_piece(QUEEN, i, j);
	else if(board[i][j] == WHITE_Q) add_white_piece(QUEEN, i, j);
	else { /* nothing, it is just empty */ }
      }
  }
  // white in minus and black in major 
  void print_board() { 
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
	if(board[i][j] == BLACK_P) printf("P");
	else if(board[i][j] == WHITE_P) printf("p");
	else if(board[i][j] == BLACK_R) printf("R");
	else if(board[i][j] == WHITE_R) printf("r");
	else if(board[i][j] == BLACK_N) printf("K");
	else if(board[i][j] == WHITE_N) printf("k");
	else if(board[i][j] == BLACK_B) printf("B");
	else if(board[i][j] == WHITE_B) printf("b");
	else if(board[i][j] == BLACK_K) printf("K");
	else if(board[i][j] == WHITE_K) printf("k");
	else if(board[i][j] == BLACK_Q) printf("Q");
	else if(board[i][j] == WHITE_Q) printf("q");
	else printf("."); 
      }
      printf("\n");
    }
    printf("\n");
  }
  // white in minus and black in major
  // white is white and black is blue
  void print_board_with_color() { 
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
	if(board[i][j] == BLACK_P) printf("P");
	else if(board[i][j] == WHITE_P) printf("\e[34mp\e[39m");
	else if(board[i][j] == BLACK_R) printf("R");
	else if(board[i][j] == WHITE_R) printf("\e[34mr\e[39m");
	else if(board[i][j] == BLACK_N) printf("K");
	else if(board[i][j] == WHITE_N) printf("\e[34mk\e[39m");
	else if(board[i][j] == BLACK_B) printf("B");
	else if(board[i][j] == WHITE_B) printf("\e[34mb\e[39m");
	else if(board[i][j] == BLACK_K) printf("K");
	else if(board[i][j] == WHITE_K) printf("\e[34mk\e[39m");
	else if(board[i][j] == BLACK_Q) printf("Q");
	else if(board[i][j] == WHITE_Q) printf("\e[34mq\e[39m");
	else printf("."); 
      }
      printf("\n");
    }
    printf("\n");
  }
  bool BLACK_P_can_move_fwd(int _i, int _j) {
    if(_i==nbl-1) return false;
    if(board[_i+1][_j]!=EMPTY) return false;
    return true;
  }
  bool BLACK_P_can_eat_left(int _i, int _j) {
    if(_i==(nbl-1)) return false;
    if(_j==0) return false;
    if(is_white(board[_i+1][_j-1])) return true;
    return false;
  }
  bool BLACK_P_can_eat_right(int _i, int _j) {
    if(_i==(nbl-1)) return false;
    if(_j==(nbc-1)) return false;
    if(is_white(board[_i+1][_j+1])) return true;
    return false;
  }
  bool WHITE_P_can_move_fwd(int _i, int _j) {
    if(_i==0) return false;
    if(board[_i-1][_j]!=EMPTY) return false;
    return true;
  }
  bool WHITE_P_can_eat_left(int _i, int _j) {
    if(_i==0) return false;
    if(_j==0) return false;
    if(is_black(board[_i-1][_j-1])) return true;
    return false;
  }
  bool WHITE_P_can_eat_right(int _i, int _j) {
    if(_i==0) return false;
    if(_j==(nbc-1)) return false;
    if(is_black(board[_i-1][_j+1])) return true;
    return false;
  }
  
};
#endif
