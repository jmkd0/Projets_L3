#ifndef MYTAQ_H
#define MYTAQ_H
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#define NBL 3
#define NBC 3
int board[NBL][NBC];
#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3


void init_board() {
    for(int i = 0; i < NBL; i++)
        for(int j = 0; j < NBC; j++)
            board[i][j] = i*NBC+j+1;
}

void print_board() {
    printf("%d %d ", NBL, NBC);
  for(int i = 0; i < NBL; i++)
  for(int j = 0; j < NBC; j++) {
      if(board[i][j] == NBL*NBC) printf("* ");
      else printf("%d ", board[i][j]);

}
printf("\n");
}

bool can_move_U(int _i, int _j) {
    if(_i <= 0) return false; else return true;

}

void move_U(int _i, int _j) {
    board[_i][_j]=board[_i-1][_j]; board[_i-1][_j]=NBL*NBC;
}
bool can_move_D(int _i, int _j) {
    if(_i >= (NBL-1)) return false; else return true;
}
void move_D(int _i, int _j) {
    board[_i][_j]=board[_i+1][_j]; board[_i+1][_j]=NBL*NBC;
}
bool can_move_L(int _i, int _j) {
    if(_j<=0) return false; else return true;
}

void move_L(int _i, int _j) {
    board[_i][_j]=board[_i][_j-1]; board[_i][_j-1]=NBL*NBC;
}
bool can_move_R(int _i, int _j) {
    if(_j>=NBC-1) return false; else return true;
}
void move_R(int _i, int _j) {
    board[_i][_j]=board[_i][_j+1]; board[_i][_j+1]=NBL*NBC;
}

void set_next(int *_moves, int& _size, int& _line, int& _col) {
    for(int i = 0; i < NBL; i++)
        for(int j = 0; j < NBC; j++) {
            if(board[i][j] == NBL*NBC) {
                _line = i; _col = j; break;
            }
        }
        _size = 0;
        if(can_move_U(_line, _col)) { _moves[_size]=MOVE_U; _size++; }
        if(can_move_D(_line, _col)) { _moves[_size]=MOVE_D; _size++; }
        if(can_move_L(_line, _col)) { _moves[_size]=MOVE_L; _size++; }
        if(can_move_R(_line, _col)) { _moves[_size]=MOVE_R; _size++; }
}

void play(int _move, int _line, int _col) {
    if(_move == MOVE_U) move_U(_line, _col);
    if(_move == MOVE_D) move_D(_line, _col);
    if(_move == MOVE_L) move_L(_line, _col);
    if(_move == MOVE_R) move_R(_line, _col);
}
void unplay(int _move, int _line, int _col) {
    if(_move == MOVE_U) move_D(_line-1, _col);
    if(_move == MOVE_D) move_U(_line+1, _col);
    if(_move == MOVE_L) move_R(_line, _col-1);
    if(_move == MOVE_R) move_L(_line, _col+1);
}

int rand_move() {
    int next_moves[4];
    int next_size;
    int next_i_line;
    int next_i_col;

    set_next(next_moves, next_size, next_i_line, next_i_col);
    int r = ((int)rand())%next_size;
    play(next_moves[r], next_i_line, next_i_col);
    return next_moves[r];
}
bool final_position() {
    for(int i = 0; i < NBL; i++)
        for(int j = 0; j < NBC; j++)
            if(board[i][j] != i*NBC+j+1) return false;
    return true;
}
std::string mkH() {
    char strh[1024];
    strh[0] ='\0';
    for(int i = 0; i < NBL; i++)
        for(int j = 0; j < NBC; j++) {
            char stre[16];
            sprintf(stre, "%d-", board[i][j]);
            strcat(strh, stre);
        }
    return std::string(strh);

}
#endif
