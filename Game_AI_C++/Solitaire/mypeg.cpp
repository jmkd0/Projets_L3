#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include "mypeg.h"
int DLS_MAX_DEPTH = 35;
std::unordered_map<std::string, int> H;
int solution_pos[36];
int solution_dir[36];
int sol_size = 0;
peg_t dls_board[36];

void dls_solve(peg_t _board, std::string _strboard, int _depth) {
    if(sol_size != 0) return;
    H[_strboard] = _depth;
    if(_board.score() == 1 && _board.board[24] == PIECE_POS) {
        sol_size = _depth; return;
    }
    if(_depth == DLS_MAX_DEPTH) return;
    for(int j = 0; j < (int)_board.move_pos.size(); j++) {
        dls_board[_depth].copy(_board);
        dls_board[_depth].play_move(_board.move_pos[j], _board.move_dir[j]);
        std::string strboard = dls_board[_depth].mkH();
        std::unordered_map<std::string, int>::iterator ii = H.find(strboard);
        if(ii == H.end()) {
            solution_pos[_depth] = _board.move_pos[j];
            solution_dir[_depth] = _board.move_dir[j];
            dls_solve(dls_board[_depth], strboard, _depth+1);
            if(sol_size != 0) break;
        }
    }

}

int main(int _ac, char** _av) {
    if(_ac != 2) { printf("usage: %s PEG_FILE\n", _av[0]); return 0; }
    peg_t G;
    G.init(7,7);
    G.load(_av[1]);
    for(int i = 0; i < DLS_MAX_DEPTH+1; i++) dls_board[i].init(G.nbl, G.nbc);
    std::string strboard = G.mkH();
    dls_solve(G, strboard, 0);
    printf("sol_size: %d\n", sol_size);
    for(int i = 0; i < sol_size; i++)
    printf("%d-%c ", solution_pos[i], cmove[solution_dir[i]]);
    printf("\n");
return 0;
}
