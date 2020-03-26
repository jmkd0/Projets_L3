#ifndef MYBT_H
#include "mybt.h"



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
  void monte_carlo1(int _log=0, int _nb_playout=1000) {
    while(terminal() == EMPTY) {
      bt_move_t m = get_monte_carlo_move( _nb_playout );
      play(m);
      if(_log) {printf("\n"); m.print(); print_board();}
    }
  }
#endif /* MYBT_H */