#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include "mytaq.h"

std::unordered_map<std::string, int> H;
int DLS_MAX_DEPTH = 30;
int* sol;
int sol_size;
void dls_solve(std::string _strboard, int _depth) {
    if(sol_size != 0) return;
    H[_strboard] = _depth;
    if(final_position()) {
        sol_size = _depth;
    return;
    }
    if(_depth == DLS_MAX_DEPTH) return;
    int next_moves[4];
    int next_size = 0;
    int next_start_line = 0;
    int next_start_col = 0;
    set_next(next_moves, next_size, next_start_line, next_start_col);
    for(int j = 0; j < next_size; j++) {
    play(next_moves[j], next_start_line, next_start_col);
    std::string new_strboard = mkH();
    std::unordered_map<std::string, int>::iterator ii = H.find(new_strboard);
    if(ii == H.end() || ii->second > _depth) {
        sol[_depth] = next_moves[j];
        dls_solve(new_strboard, _depth+1);
    }
    unplay(next_moves[j], next_start_line, next_start_col);
    if(sol_size != 0) break;
    }
}

int IDS_MAX_DEPTH = 30;
//int* sol;
//int sol_size;
void ids_solve() {
    sol_size = 0;
    std::string strboard = mkH();
    for(int k = 1; k < IDS_MAX_DEPTH; k++) {
        H.clear();
        DLS_MAX_DEPTH = k;
        dls_solve(strboard, 0);
        if(sol_size != 0) break;
    }
}
int main(int _ac, char** _av) {
    sol_size = 0;
    sol = new int[IDS_MAX_DEPTH];
    board[0][0] = 1; board[0][1] = 2; board[0][2] = 3;
    board[1][0] = 4; board[1][1] = 9; board[1][2] = 5;
    board[2][0] = 6; board[2][1] = 7; board[2][2] = 8;
    ids_solve();
    if(sol_size != 0) {
        for(int i = 0; i < sol_size; i++)
            printf("%d ", sol[i]);
        printf("\n");
    }
    delete[] sol;
    return 0;
}
