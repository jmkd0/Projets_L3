#ifndef MYPEG_H
#define MYPEG_H
#include <cstdio>
#include <cstdlib>
#include <vector>
#define OUT_OF_BOARD 0
#define FREE_POS 1
#define PIECE_POS 2

#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3
char cmove[] = {'U', 'D', 'L', 'R'};
char cpos[] = {'.', '+', 'o'};
struct peg_t {

int board[49];
int nbl;
int nbc;
std::vector<int> move_pos;
std::vector<int> move_dir;
void init(int _nbl, int _nbc) {
    nbl = _nbl; nbc = _nbc;
    for(int i = 0; i < nbl*nbc; i++) board[i] = OUT_OF_BOARD;
    move_pos.reserve(10);
    move_dir.reserve(10);
}
void add_move(int _pos, int _dir) {
    move_pos.push_back(_pos);
    move_dir.push_back(_dir);
}
void copy(peg_t _b) {
    if(nbl != _b.nbl || nbc != _b.nbc) return;
    for(int i = 0; i < nbl*nbc; i++) board[i] = _b.board[i];
    for(int i = 0; i < (int)_b.move_pos.size(); i++)
    add_move(_b.move_pos[i], _b.move_dir[i]);
}
void load(char* _file) {
    FILE *fp = fopen(_file, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    if (fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); }
    int nbline = 0;
    while ((nread = getline(&line, &len, fp)) != -1) {
    if(((int)nread) == (nbc+1)) {
        for(int i = 0; i < nbc; i++) {
            if(line[i] == cpos[FREE_POS]) board[nbline*nbc+i] = FREE_POS;
            if(line[i] == cpos[PIECE_POS]) board[nbline*nbc+i] = PIECE_POS;
        }
    nbline++;
    }
    if(nbline == nbl) break;
    }
    free(line); fclose(fp); init_moves();
}
std::string mkH() {
    char strh[1024];
    int strh_size = 0;
    for(int i = 0; i < nbl; i++)
        for(int j = 0; j < nbc; j++) {
            if(board[i*nbc+j] == OUT_OF_BOARD) { /* nop */ }
            else if(board[i*nbc+j] == FREE_POS) { strh[strh_size] = '+'; strh_size++; }
                    else { strh[strh_size] = 'o'; strh_size++; }
        }
    strh[strh_size] = '\0';
    return std::string(strh);
}

bool can_move_U(int _p) {
    if(_p >= nbl*nbc || _p < 2*nbc) return false;
    if(board[_p] != PIECE_POS) return false;
    if(board[_p-nbc] != PIECE_POS) return false;
    if(board[_p-2*nbc] != FREE_POS) return false;
    return true;
}

void move_U(int _p) {
    board[_p]=FREE_POS; board[_p-nbc]=FREE_POS; board[_p-2*nbc]=PIECE_POS;
}

bool can_move_D(int _p) {
    if(_p < 0 || _p > ((nbl*nbc)-2*nbc)) return false;
    if(board[_p] != PIECE_POS) return false;
    if(board[_p+nbc] != PIECE_POS) return false;
    if(board[_p+2*nbc] != FREE_POS) return false;
    return true;
}

void move_D(int _p) {
    board[_p]=FREE_POS; board[_p+nbc]=FREE_POS; board[_p+2*nbc]=PIECE_POS;
}
bool can_move_L(int _p) {
    if(_p < 0 || _p >= nbl*nbc || (_p%nbc) <= 1) return false;
    if(board[_p] != PIECE_POS) return false;
    if(board[_p-1] != PIECE_POS) return false;
    if(board[_p-2] != FREE_POS) return false;
    return true;
}

void move_L(int _p) {
    board[_p]=FREE_POS; board[_p-1]=FREE_POS; board[_p-2]=PIECE_POS;
}

bool can_move_R(int _p) {
    if(_p < 0 || _p >= nbl*nbc || (_p%nbc) >= (nbc-2)) return false;
    if(board[_p] != PIECE_POS) return false;
    if(board[_p+1] != PIECE_POS) return false;
    if(board[_p+2] != FREE_POS) return false;
    return true;
}

void move_R(int _p) {
    board[_p]=FREE_POS; board[_p+1]=FREE_POS; board[_p+2]=PIECE_POS;
}

void try_add_move_from(int _p) {
    if(can_move_U(_p)) add_move(_p, MOVE_U);
    if(can_move_D(_p)) add_move(_p, MOVE_D);
    if(can_move_L(_p)) add_move(_p, MOVE_L);
    if(can_move_R(_p)) add_move(_p, MOVE_R);
}

void try_add_move_to(int _p) {
    if(can_move_U(_p+2*nbc)) add_move(_p+2*nbc, MOVE_U);
    if(can_move_D(_p-2*nbc)) add_move(_p-2*nbc, MOVE_D);
    if(can_move_L(_p+2)) add_move(_p+2, MOVE_L);
    if(can_move_R(_p-2)) add_move(_p-2, MOVE_R);
}

void init_moves(){
    for(int i = 0; i < nbc*nbl; i++) {
        if(board[i] == FREE_POS) try_add_move_to(i);
    }
}

void update_moves() {
    move_pos.clear(); move_dir.clear(); init_moves();
}

int score() {
    int ret = 0;
    for(int i = 0; i < nbc*nbl; i++) if(board[i] == PIECE_POS) ret++;
    return ret;
}

void play_move(int _pos, int _dir) {
    if(_dir == MOVE_U) { move_U(_pos); }
    else if(_dir == MOVE_D) { move_D(_pos); }
        else if(_dir == MOVE_L) {move_L(_pos); }
            else if(_dir == MOVE_R) {move_R(_pos); }
    update_moves();
  }
};
#endif
