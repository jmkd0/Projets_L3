#ifndef MYBT_H
#define MYBT_H
#include <cstdio>
#include <cstdlib>
#include <string.h>
#define WHITE 0
#define BLACK 1
#define EMPTY 2
char* cboard = (char*)"ox.";

struct bt_piece_t {
  int line; int col;
};
struct bt_move_t {
  int line_i; int col_i;
  int line_f; int col_f;
  void print() {
    printf("(move %d %d %d %d)\n", line_i, col_i, line_f, col_f);
  }			
};
#define MAX_LINES 10
#define MAX_COLS 10
struct bt_t {
  int nbl;
  int nbc;
  int board[MAX_LINES][MAX_COLS];
  int turn;

  bt_piece_t white_pieces[2*MAX_LINES];
  int nb_white_pieces;
  bt_piece_t black_pieces[2*MAX_LINES];
  int nb_black_pieces;
  bt_move_t moves[3*2*MAX_LINES];
  int nb_moves;
  int moves_update_turn;
  
  void init(int _nbl, int _nbc) {
    nbl = _nbl; nbc = _nbc;
    turn = 0;
    moves_update_turn = -1;
    for(int i = 0; i < nbl; i++)
      for(int j = 0; j < nbc; j++) {
	if(i <= 1 ) {
	  board[i][j] = WHITE;
	} else if(i < _nbl-2) {
	     board[i][j] = EMPTY;
	} else {
	  board[i][j] = BLACK;
	}
      }
    init_pieces();
    update_moves();
  }
  void init_pieces() {
    nb_white_pieces = 0;
    nb_black_pieces = 0;
    for(int i = 0; i < nbl; i++)
      for(int j = 0; j < nbc; j++) {
	if(board[i][j] == WHITE) {
	  white_pieces[nb_white_pieces].line = i;
	  white_pieces[nb_white_pieces].col = j;
	  nb_white_pieces++;
	} else if(board[i][j] == BLACK) {
	  black_pieces[nb_black_pieces].line = i;
	  black_pieces[nb_black_pieces].col = j;
	  nb_black_pieces++;
	}
      }
  }
  bool white_move_right(int _line, int _col) {
    if(board[_line][_col] != WHITE) return false;
    if(_line == nbl-1) return false;
    if(_col == nbc-1) return false;
    if(board[_line+1][_col+1] == WHITE) return false;
    return true;
  }
  bool white_move_forward(int _line, int _col) {
    if(board[_line][_col] != WHITE) return false;
    if(_line == nbl-1) return false;
    if(board[_line+1][_col] != EMPTY) return false;
    return true;
  }
  bool white_move_left(int _line, int _col) {
    if(board[_line][_col] != WHITE) return false;
    if(_line == nbl-1) return false;
    if(_col == 0) return false;
    if(board[_line+1][_col-1] == WHITE) return false;
    return true;
  }
  bool black_move_right(int _line, int _col) {
    if(board[_line][_col] != BLACK) return false;
    if(_line == 0) return false;
    if(_col == nbc-1) return false;
    if(board[_line-1][_col+1] == BLACK) return false;
    return true;
  }
  bool black_move_forward(int _line, int _col) {
    if(board[_line][_col] != BLACK) return false;
    if(_line == 0) return false;
    if(board[_line-1][_col] != EMPTY) return false;
    return true;
  }
  bool black_move_left(int _line, int _col) {
    if(board[_line][_col] != BLACK) return false;
    if(_line == 0) return false;
    if(_col == 0) return false;
    if(board[_line-1][_col-1] == BLACK) return false;
    return true;
  }
  void print_board() {
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
	printf("%c ", cboard[board[i][j]]);
      }
      printf("\n");
    }
  }
  void update_moves() {
    if(turn%2 == 0) update_moves(WHITE);
    else update_moves(BLACK);
  }
  void update_moves(int _color) {
    if(moves_update_turn == turn) return; // MAJ déjà faite
    moves_update_turn = turn;
    nb_moves = 0;
    if(_color==WHITE) {
      for(int i = 0; i < nb_white_pieces; i++) {
	int li = white_pieces[i].line;
	int ci = white_pieces[i].col;
	if(white_move_right(li, ci)) {
	  moves[nb_moves].line_i = li;
	  moves[nb_moves].col_i = ci;
	  moves[nb_moves].line_f = li+1;
	  moves[nb_moves].col_f = ci+1;
	  nb_moves++;
	}
	if(white_move_forward(li, ci)) {
	  moves[nb_moves].line_i = li;
	  moves[nb_moves].col_i = ci;
	  moves[nb_moves].line_f = li+1;
	  moves[nb_moves].col_f = ci;
	  nb_moves++;
	}
	if(white_move_left(li, ci)) {
	  moves[nb_moves].line_i = li;
	  moves[nb_moves].col_i = ci;
	  moves[nb_moves].line_f = li+1;
	  moves[nb_moves].col_f = ci-1;
	  nb_moves++;
	}
      }
    } else if(_color == BLACK) {
      for(int i = 0; i < nb_black_pieces; i++) {
	int li = black_pieces[i].line;
	int ci = black_pieces[i].col;
	if(black_move_right(li, ci)) {
	  moves[nb_moves].line_i = li;
	  moves[nb_moves].col_i = ci;
	  moves[nb_moves].line_f = li-1;
	  moves[nb_moves].col_f = ci+1;
	  nb_moves++;
	}
	if(black_move_forward(li, ci)) {
	  moves[nb_moves].line_i = li;
	  moves[nb_moves].col_i = ci;
	  moves[nb_moves].line_f = li-1;
	  moves[nb_moves].col_f = ci;
	  nb_moves++;
	}
	if(black_move_left(li, ci)) {
	  moves[nb_moves].line_i = li;
	  moves[nb_moves].col_i = ci;
	  moves[nb_moves].line_f = li-1;
	  moves[nb_moves].col_f = ci-1;
	  nb_moves++;
	}
      }
    }
    if(nb_moves == 0) {
      moves[nb_moves].line_i = -1;
      nb_moves = 1;
    }
  }
  bt_move_t get_rand_move() {
    update_moves();
    int r = ((int)rand())%nb_moves;
    return moves[r];
  }
  void play(bt_move_t _m) {
    if(_m.line_i != -1) {
      int color_i = board[_m.line_i][_m.col_i];
      int color_f = board[_m.line_f][_m.col_f];
      board[_m.line_f][_m.col_f] = board[_m.line_i][_m.col_i];
      board[_m.line_i][_m.col_i] = EMPTY;
      if(color_i == WHITE) {
	for(int i = 0; i < nb_white_pieces; i++) {
	  if(white_pieces[i].line == _m.line_i &&
	     white_pieces[i].col == _m.col_i) {
	    white_pieces[i].line = _m.line_f;
	    white_pieces[i].col = _m.col_f;
	    break;
	  }
	}
	if(color_f == BLACK) {
	  for(int i = 0; i < nb_black_pieces; i++) {
	    if(black_pieces[i].line == _m.line_f &&
	       black_pieces[i].col == _m.col_f) {
	      black_pieces[i] = black_pieces[nb_black_pieces-1];
	      nb_black_pieces--;
	      break;
	    }
	  }
	}
      } else if(color_i == BLACK) {
	for(int i = 0; i < nb_black_pieces; i++) {
	  if(black_pieces[i].line == _m.line_i &&
	     black_pieces[i].col == _m.col_i) {
	    black_pieces[i].line = _m.line_f;
	    black_pieces[i].col = _m.col_f;
	    break;
	  }
	}
	if(color_f == WHITE) {
	  for(int i = 0; i < nb_white_pieces; i++) {
	    if(white_pieces[i].line == _m.line_f &&
	       white_pieces[i].col == _m.col_f) {
	      white_pieces[i] = white_pieces[nb_white_pieces-1];
	      nb_white_pieces--;
	      break;
	    }
	  }
	}
      }
    }
    turn++;
    if(_m.line_i != -1) update_moves();
  }
  int terminal() {
    for(int i = 0; i < nbc; i++) {
      if(board[0][i] == BLACK) return BLACK;
    }
    for(int i = 0; i < nbc; i++) {
      if(board[nbl-1][i] == WHITE) return WHITE;
    }
    return EMPTY;
  }
  double score(int _color) {
    int state = terminal();
    if(state == EMPTY) return 0.0;
    if(_color == state) return 1.0;
    return -1.0;
  }
  void playout(int _log=0) {
    while(terminal() == EMPTY) {
      bt_move_t m = get_rand_move();
      play(m);
      if(_log) {printf("\n"); m.print(); print_board();}
    }
  }
  std::string mkH() {
    static char strh[1024];
    int strh_size = 0;
    for(int i = 0; i < nbl; i++)
      for(int j = 0; j < nbc; j++) {
        strh[strh_size] = cboard[board[i][j]];
        strh_size++;
      }
    strh[strh_size]  ='0'+turn/100;
    strh_size++;
    strh[strh_size]  ='0'+(turn%100)/10;
    strh_size++;
    strh[strh_size]  ='0'+(turn%100)%10;
    strh_size++;
    strh[strh_size] = '\0';
    return std::string(strh);
  }
//Résolutions avec Random
  bt_move_t get_rand_move_1() {
    update_moves();
    int r = ((int)rand())%nb_moves;
    return moves[r];
  }
  void playout_random(int _log=0) {
    while(terminal() == EMPTY) {
      bt_move_t m = get_rand_move_1();
      play(m);
      if(_log) {printf("\n"); m.print(); print_board();}
    }
  }
  //Résolutions avec Monte Carlo
  bt_move_t get_monte_carlo_move(int _nb_playout) {
    update_moves();
    //On memorise le plateau et les moves
    bt_move_t  moves_mc[3*2*MAX_LINES];
    memcpy(moves_mc, moves, sizeof(bt_move_t)*3*2*MAX_LINES); 
    int board_mc[MAX_LINES][MAX_COLS];
    memcpy(board_mc, board, sizeof(int)*MAX_LINES*MAX_COLS);
    int nb_white_pieces_mc = nb_white_pieces;
    int nb_black_pieces_mc = nb_black_pieces;
    int turn_mc = turn;
    bt_piece_t white_pieces_mc[2*MAX_LINES];
    memcpy(white_pieces_mc, white_pieces, sizeof(bt_piece_t)*2*MAX_LINES);
    bt_piece_t black_pieces_mc[2*MAX_LINES];
    memcpy(black_pieces_mc, black_pieces, sizeof(bt_piece_t)*2*MAX_LINES);

    int r = MC(_nb_playout );
    //on retablie le plateau
    
    memcpy(moves, moves_mc , sizeof(bt_move_t)*3*2*MAX_LINES);  
    memcpy(board, board_mc, sizeof(int)*MAX_LINES*MAX_COLS);
    nb_white_pieces = nb_white_pieces_mc;
    nb_black_pieces = nb_black_pieces_mc;
    turn = turn_mc;
    memcpy(white_pieces, white_pieces_mc, sizeof(bt_piece_t)*2*MAX_LINES);
    memcpy(black_pieces, black_pieces_mc, sizeof(bt_piece_t)*2*MAX_LINES);
    return moves[r];
  }
  int MC(int _nb_playout){
    int count, move_win=0, max=0;
    for (int i=0; i<nb_moves; i++){
        count = 0;
      for (int j=0; j< _nb_playout; j++){
        bt_move_t  m = moves[i];
        play(m);
        while(terminal() == EMPTY) {
          m = get_rand_move_1();
          play(m);
        }
        if( score(BLACK) == 1) count++;
      }
      if(count > max){ 
        max=count;
        move_win = i;
      }
    }
    return move_win;
  }
  void monte_carlo(int _log=0, int _nb_playout=1000) {
    while(terminal() == EMPTY) {
      bt_move_t m = get_monte_carlo_move( _nb_playout );
      play(m);
      if(_log) {printf("\n"); m.print(); print_board();}
    }
  }
  //Résolutions avec Monte Carlo Tree Search
  bt_move_t get_monte_carlo_tree_search_move() {
    update_moves();
    int r =1;/* valeur de r à déterminer avec monte carlo tree search*/
    return moves[r];
  }
  void monte_carlo_tree_search(int _log=0) {
    while(terminal() == EMPTY) {
      bt_move_t m = get_monte_carlo_tree_search_move();
      play(m);
      if(_log) {printf("\n"); m.print(); print_board();}
    }
  }



  //Résolutions avec Nested Monte Carlo Search
  void nested_monte_carlo(int _log=0, int level) {
    while(terminal() == EMPTY) {
      bt_move_t m = get_nested_monte_carlo_move( level_max );
      play(m);
      if(_log) {printf("\n"); m.print(); print_board();}
    }
  }
  bt_move_t  get_nested_monte_carlo_move (int level){
    update_moves();
    //On memorise le plateau et les moves
    bt_move_t  moves_nmcs[3*2*MAX_LINES];
    memcpy(moves_nmcs, moves, sizeof(bt_move_t)*3*2*MAX_LINES); 
    int board_nmcs[MAX_LINES][MAX_COLS];
    memcpy(board_nmcs, board, sizeof(int)*MAX_LINES*MAX_COLS);
    int nb_white_pieces_nmcs = nb_white_pieces;
    int nb_black_pieces_nmcs = nb_black_pieces;
    int turn_nmcs = turn;
    bt_piece_t white_pieces_nmcs[2*MAX_LINES];
    memcpy(white_pieces_nmcs, white_pieces, sizeof(bt_piece_t)*2*MAX_LINES);
    bt_piece_t black_pieces_nmcs[2*MAX_LINES];
    memcpy(black_pieces_nmcs, black_pieces, sizeof(bt_piece_t)*2*MAX_LINES);

    int r = NMCS(level_max); //application de la methode de NESTED MONTE CARLO SEARCH
    //on retablie le plateau
    
    memcpy(moves, moves_nmcs , sizeof(bt_move_t)*3*2*MAX_LINES);  
    memcpy(board, board_nmcs, sizeof(int)*MAX_LINES*MAX_COLS);
    nb_white_pieces = nb_white_pieces_nmcs;
    nb_black_pieces = nb_black_pieces_nmcs;
    turn = turn_nmcs;
    memcpy(white_pieces, white_pieces_nmcs, sizeof(bt_piece_t)*2*MAX_LINES);
    memcpy(black_pieces, black_pieces_nmcs, sizeof(bt_piece_t)*2*MAX_LINES);
    return moves[r];
  }

  int NMCS(){
      while(terminal() == EMPTY) {
        for (int i=0; i< nb_moves; i++){
          bt_move_t  m = moves[i];
          play(m);
        }
          m = get_rand_move_1();
          play(m);
        }
  }
};
#endif /* MYBT_H */
