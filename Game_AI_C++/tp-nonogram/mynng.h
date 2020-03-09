#ifndef MYNNG_H
#define MYNNG_H
#include <cstdio>
#include <cstdlib>
#include <vector>
#define WHITE 0
#define BLACK 1
char* cboard = (char*)".X";

struct nng_move_t {
  int line; int col;
};
#define MAX_CONSTRAINTS 5
#define MAX_LINES 10
#define MAX_COLS 10
struct nng_t {
  int nbl;
  int nbc;
  int problem_c_lines[MAX_LINES][MAX_CONSTRAINTS];
  int problem_nb_c_lines[MAX_LINES];
  int problem_c_cols[MAX_COLS][MAX_CONSTRAINTS];
  int problem_nb_c_cols[MAX_COLS];
  int problem_sum_c_lines;
  int problem_max_nbc_lines[MAX_LINES];
  int problem_max_nbc_cols[MAX_COLS];
  
  int board_lines_id[MAX_LINES][MAX_COLS];
  int board_cols_id[MAX_LINES][MAX_COLS];
  int board_max_nbc_lines[MAX_COLS];
  int board_max_nbc_cols[MAX_LINES];
  int board_nb_c_lines[MAX_LINES];
  int board_c_lines[MAX_LINES][MAX_CONSTRAINTS]; // !!! FIRST INDEX = LID
  int board_nb_c_cols[MAX_COLS];
  int board_c_cols[MAX_COLS][MAX_CONSTRAINTS]; // !!! FIRST INDEX = CID

  int board[MAX_LINES][MAX_COLS];
  int nb_val_set;

  void print_board() {
    printf("problem_sum_c_lines: %d\n", problem_sum_c_lines);
    printf("nb_val_set: %d\n", nb_val_set);
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
        printf("%c ", cboard[board[i][j]]);
      }
      printf("\n");
    }
  }
  void print_board_info(){
    printf("lines_id __ cols_id : \n");
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
        if(board_lines_id[i][j]!=-1) printf(" ");
        printf("%d ", board_lines_id[i][j]);
      }
      printf("__   ");
      for(int j = 0; j < nbc; j++) {
        if(board_cols_id[i][j]!=-1) printf(" ");
        printf("%d ", board_cols_id[i][j]);
      }
      printf("\n");
    }
    printf("board_max_nbc_lines : ");
    for(int i = 0; i < nbc; i++) printf("%d ", board_max_nbc_lines[i]);
    printf("\nboard_max_nbc_cols : ");
    for(int i = 0; i < nbl; i++) printf("%d ", board_max_nbc_cols[i]);
    printf("\nboard_c_lines : ");
    for(int i = 0; i < nbl; i++) {
      printf("(");
      for(int j = 0; j < board_nb_c_lines[i]; j++) {
            printf("%d ", board_c_lines[i][j]);
      }
      printf(") ");
    }
    printf("\nboard_c_cols : ");
    for(int i = 0; i < nbc; i++) {
      printf("(");
      for(int j = 0; j < board_nb_c_cols[i]; j++) {
        printf("%d ", board_c_cols[i][j]);
      }
      printf(") ");
    }
    printf("\n");
  }
  void print_problem_info() {
    printf("lines %d : ", nbl);
    for(int i = 0; i < nbl; i++) {
      printf("(");
      for(int j = 0; j < problem_nb_c_lines[i]; j++) {
        printf("%d ", problem_c_lines[i][j]);
      }
      printf(") ");
    }
    printf("\ncols %d : ", nbc);
    for(int i = 0; i < nbc; i++) {
      printf("(");
      for(int j = 0; j < problem_nb_c_cols[i]; j++) {
        printf("%d ", problem_c_cols[i][j]);
      }
      printf(") ");
    }
    printf("\n");
    printf("problem_max_nbc_lines : ");
    for(int i = 0; i < nbl; i++)
      printf("%d ", problem_max_nbc_lines[i]);
    printf("\n");
    printf("problem_max_nbc_cols : ");
    for(int i = 0; i < nbc; i++)
      printf("%d ", problem_max_nbc_cols[i]);
    printf("\n");
  }
  void copy(nng_t& _n) {
    memcpy(this, &_n, sizeof(nng_t));
  }
  void init(int _nbl, int _nbc) {
    nbl = _nbl; nbc = _nbc;
    for(int i = 0; i < nbl; i++)
      for(int j = 0; j < nbc; j++) {
        board[i][j] = WHITE;
        board_lines_id[i][j] = -1;
        board_cols_id[i][j] = -1;
      }
    for(int i = 0; i < nbc; i++) {
      board_max_nbc_lines[i] = 0;
      for(int j = 0; j < MAX_CONSTRAINTS; j++) board_c_lines[i][j] = 0;
    }
    for(int i = 0; i < nbl; i++) {
      board_max_nbc_cols[i] = 0;
      for(int j = 0; j < MAX_CONSTRAINTS; j++) board_c_cols[i][j] = 0;
    }
    nb_val_set = 0;
  }
  void set_max() {
    for(int i = 0; i < nbl; i++) {
      problem_max_nbc_lines[i] = 0;
      for(int j = 0; j < problem_nb_c_lines[i]; j++) {
        if(problem_c_lines[i][j] > problem_max_nbc_lines[i]) problem_max_nbc_lines[i] = problem_c_lines[i][j];
      }
    }
    for(int i = 0; i < nbc; i++) {
      problem_max_nbc_cols[i] = 0;
      for(int j = 0; j < problem_nb_c_cols[i]; j++) {
        if(problem_c_cols[i][j] > problem_max_nbc_cols[i]) problem_max_nbc_cols[i] = problem_c_cols[i][j];
      }
    }
  }
  void set_line_id(int _lid) {
    for(int i = 0; i < nbc; i++) board_lines_id[_lid][i] = -1;
    int curr_id = 0;
    int curr_gid = 0;
    int curr_val = board[_lid][0];
    board_lines_id[_lid][0] = curr_id;
    int best_lines_size = 0;
    int curr_lines_size = 0;
    if(board[_lid][0] == BLACK) {
      best_lines_size = 1;
      curr_lines_size = 1;
    }
    for(int i = 1; i < nbc; i++) {
      if(board[_lid][i] == curr_val) {
        board_lines_id[_lid][i] = curr_id;
        curr_lines_size ++;
      } else {
        if(board[_lid][i] == WHITE) {
          if(best_lines_size < curr_lines_size)
            best_lines_size = curr_lines_size;
          board_c_lines[_lid][curr_gid] = curr_lines_size;
          curr_gid++;
          board_nb_c_lines[_lid] = curr_gid;
        }
        curr_val = board[_lid][i];
        ++curr_id;
        board_lines_id[_lid][i] = curr_id;
        curr_lines_size = 1;
      }
    }
    if(board[_lid][nbc-1] == BLACK) {
      if(best_lines_size < curr_lines_size)
        best_lines_size = curr_lines_size;
      board_c_lines[_lid][curr_gid] = curr_lines_size;
      board_nb_c_lines[_lid] = curr_gid+1;
    }
    board_max_nbc_lines[_lid] = best_lines_size;
  }
  void set_col_id(int _cid) {
    for(int i = 0; i < nbl; i++) board_cols_id[i][_cid] = -1;
    int curr_id = 0;
    int curr_gid = 0;
    int curr_val = board[0][_cid];
    board_cols_id[0][_cid] = curr_id;
    int best_cols_size = 0;
    int curr_cols_size = 0;
    if(board[0][_cid] == BLACK) {
      best_cols_size = 1;
      curr_cols_size = 1;
    }
    for(int i = 1; i < nbl; i++) {
      if(board[i][_cid] == curr_val) {
        board_cols_id[i][_cid] = curr_id;
        curr_cols_size ++;
      } else {
        if(board[i][_cid] == WHITE) {
          if(best_cols_size < curr_cols_size)
            best_cols_size = curr_cols_size;
          board_c_cols[_cid][curr_gid] = curr_cols_size;
          curr_gid++;
          board_nb_c_cols[_cid] = curr_gid;
        }
        curr_val = board[i][_cid];
        ++curr_id;
        board_cols_id[i][_cid] = curr_id;
        curr_cols_size = 1;
      }
    }
    if(board[nbl-1][_cid] == BLACK) {
      if(best_cols_size < curr_cols_size)
        best_cols_size = curr_cols_size;
      board_c_cols[_cid][curr_gid] = curr_cols_size;
      board_nb_c_cols[_cid] = curr_gid+1;
    }
    board_max_nbc_cols[_cid] = best_cols_size;
  }
  void load(char* _file) {
    FILE* fp;
    if ((fp = fopen(_file,"r")) == 0) {
      fprintf(stderr, "fopen %s error\n", _file); return;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t linesize = getline(&line, &len, fp);
    linesize=linesize+0; // to avoid a warning
    int new_nbl; int new_nbc;
    int max_cl; int max_cc;
    sscanf(line, "%d %d %d %d", &new_nbl, &new_nbc, &max_cl, &max_cc);
    init(new_nbl, new_nbc);
    nbl = 0; nbc = 0;
    if(max_cl > 3 || max_cc > 3) {
      printf("ERROR : max_cl > 3 || max_cc > 3\n"); exit(0);
    }
    int mode = 0; /* 0:nil 1:lines 2:cols */
    while ((read = getline(&line, &len, fp)) != -1) {
      if(strncmp(line, "lines", 5) == 0) { mode = 1; }
      else if(strncmp(line, "cols", 4) == 0) { mode = 2; }
      else {
        int vals[3];
        int nbvals = 0;
        if(sscanf(line, "%d %d %d", &vals[0], &vals[1], &vals[2]) == 3) nbvals=3;
        else if(sscanf(line, "%d %d", &vals[0], &vals[1]) == 2) nbvals=2;
        else if(sscanf(line, "%d", &vals[0]) == 1) nbvals=1;
        if(mode == 1) {
          problem_nb_c_lines[nbl] = nbvals;
          for(int i = 0; i < nbvals; i++) {
            problem_c_lines[nbl][i] = vals[i];
            problem_sum_c_lines += vals[i];
          }
          nbl++;
        }
        if(mode == 2) {
          problem_nb_c_cols[nbc] = nbvals;
          for(int i = 0; i < nbvals; i++) problem_c_cols[nbc][i] = vals[i];
          nbc++;
        }
      }
    }
    free(line);
    fclose(fp);
    if(nbl != new_nbl || nbc != new_nbc) {
      fprintf(stderr, "ERROR  : nbl %d nbc %d ... new_nbl %d new_nbc %d\n", nbl, nbc, new_nbl, new_nbc);
      exit(0);
    }
    set_max();
  }
  nng_move_t get_rand_move() {
    nng_move_t ret;
    int r = ((int)rand())%((nbl*nbc)-nb_val_set);
    printf("%d ", r);
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
        if(r == 0 && board[i][j] == WHITE) {
          ret.line = i; ret.col = j; /* printf("%d  %d\n", i, j); */ return ret;
        }
        if(board[i][j] == WHITE) r--;
      }
    }
    printf("ERROR : NO RAND MOVE\n"); exit(0);
    return ret;
  }
  int get_nb_moves() {
    return (nbl*nbc)-nb_val_set;
  }
  nng_move_t get_move(int _id) {
    nng_move_t ret;
    int id = _id;
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
        if(id == 0 && board[i][j] == WHITE) {
          ret.line = i; ret.col = j; return ret;
        }
        if(board[i][j] == WHITE) id--;
      }
    }

    printf("ERROR : NO %d MOVE\n", _id); exit(0);
    return ret;
  }
  std::vector<nng_move_t> get_all_moves() {
    std::vector<nng_move_t> ret;
    for(int i = 0; i < nbl; i++) {
      for(int j = 0; j < nbc; j++) {
        if(board[i][j] == WHITE) {
          nng_move_t mm;
          mm.line = i; mm.col = j;
          ret.push_back(mm);
        }
      }
    }
    return ret;
  }
  void play(nng_move_t _m) {
    board[_m.line][_m.col] = BLACK;
    set_line_id(_m.line);
    set_col_id(_m.col);
    nb_val_set++;
  }
  // GGP-like endgame
  // if the longest group is longer than the longest constraint
  // (in a row or column)
  // (i.e. only check mark is available, uncheck is not)
  bool terminal() {
    // all are checked
    if(nb_val_set == nbl*nbc) return true;
    // one is bigger => true
    for(int i = 0; i < nbc; i++)
      if(board_max_nbc_lines[i] > problem_max_nbc_lines[i]) return true;
    for(int i = 0; i < nbl; i++)
      if(board_max_nbc_cols[i] > problem_max_nbc_cols[i]) return true;
    // one is not equal => false;
    for(int i = 0; i < nbc; i++)
      if(board_max_nbc_lines[i] != problem_max_nbc_lines[i]) return false;
    for(int i = 0; i < nbl; i++)
      if(board_max_nbc_cols[i] != problem_max_nbc_cols[i]) return false;
    // sizes of groups are different => false
    for(int i = 0; i < nbl; i++) {
      if(board_nb_c_lines[i] != problem_nb_c_lines[i]) return false;
      for(int j = 0; j < problem_nb_c_lines[i]; j++)
        if(board_c_lines[i][j] != problem_c_lines[i][j]) return false;
    }
    for(int i = 0; i < nbc; i++) {
      if(board_nb_c_cols[i] != problem_nb_c_cols[i]) return false;
      for(int j = 0; j < problem_nb_c_cols[i]; j++)
        if(board_c_cols[i][j] != problem_c_cols[i][j]) return false;
    }
    // all are equals... so potentially the solution
    return true;
  }
  void playout() {
    while( ! terminal()) {
      nng_move_t m = get_rand_move();
      play(m);
    }
  }
  // binary game score OR GGP-like score : 0=lost 100=win
  int score() {
    for(int i = 0; i < nbl; i++) {
      if(board_nb_c_lines[i] != problem_nb_c_lines[i]) return 0;
      for(int j = 0; j < problem_nb_c_lines[i]; j++)
        if(board_c_lines[i][j] != problem_c_lines[i][j]) return 0;
    }
    for(int i = 0; i < nbc; i++) {
      if(board_nb_c_cols[i] != problem_nb_c_cols[i]) return 0;
      for(int j = 0; j < problem_nb_c_cols[i]; j++)
        if(board_c_cols[i][j] != problem_c_cols[i][j]) return 0;
    }
    return 100;
  }
  std::string mkH() {
    static char strh[1024];
    int strh_size = 0;
    for(int i = 0; i < nbl; i++)
      for(int j = 0; j < nbc; j++) {
        strh[strh_size] = cboard[board[i][j]];
        strh_size++;
      }
    strh[strh_size] = '\0';
    return std::string(strh);
  }

};
#endif /* MYNNG_H */
