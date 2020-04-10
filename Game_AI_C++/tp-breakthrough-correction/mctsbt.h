#ifndef MCTSBT_H
#define MCTSBT_H
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <math.h>
#include "mybt.h"
#define K_UCT 0.1

struct bt_node_info_t {
  bt_move_t move; // le coup joué pour arriver là (coordonnées)
  int Wi;    // nombre de victoires (victoire=1, échec=0)
  int Ni;    // nombre de visites
  bool terminal;      // sous-arbre complètement exploré
  bt_node_info_t() {
    move.line_i = -1; move.col_i = -1;
    move.line_f = -1; move.col_f = -1;
    Wi = 0;
    Ni = 0;
    terminal = false;
  }
  void print() {
    printf("move (%d %d -- %d %d) Wi %d -- Ni %d -- terminal %d\n",
	   move.line_i, move.col_i, move.line_f, move.col_f, Wi, Ni, (int)terminal);
  }
};

struct bt_node_t {
  int N;                         // nombre de descentes à partir de ce nœud
  int nb_terminal;                   // nœuds enfants complètement explorés
  std::vector<bt_node_info_t> infos; // stats des nœuds enfants
  bt_node_t() {
    N = 0;
    nb_terminal = 0;
  }
};

struct bt_MC_t {
  bt_t root_board;
  bt_t mc_board;
  int player_color;
  std::vector<bt_node_info_t> infos;
  bt_MC_t(bt_t _root_board, int _player_color) {
    player_color = _player_color;
    root_board = _root_board;
    root_board.update_moves();
    infos.resize(root_board.nb_moves);
    for(int i = 0; i < root_board.nb_moves; i++) {
      infos[i].move = root_board.moves[i];
    }
  }
  bt_move_t MC(int _seed, int _nb_playout) {
    srand(_seed);
    int k = 0;
    for(int i = 0; i < _nb_playout; i++) {
      mc_board = root_board;
      mc_board.play(infos[k].move);
      mc_board.playout();
      infos[k].Wi += mc_board.score(player_color);
      infos[k].Ni ++;
      k++;
      if(k == (int)infos.size()) k=0;
    }      
    bt_move_t best_move;
    double best_val = 0;
    for(bt_node_info_t i : infos) {
      double val_i = ((double)i.Wi)/i.Ni;
      if(val_i > best_val) {
	best_val = val_i;
	best_move = i.move;
      }
    }
    return best_move; 
  }
};

struct bt_tree_t {
  int nb_nodes_alloc;  // nb d'itérations, nb de nœuds à prévoir dans l'arbre
  int nb_nodes;        // nb de noeuds dans l'arbre (utilisé pour node_id)
  int* descent_pid;    // parent id: T idx à chaque pas (size: descent_alloc)
  int* descent_cid;    // children id: infos idx à chq pas (size: descent_alloc)
  int descent_alloc;   // profondeur max d'exploration
  int descent_size;    // profondeur courante d'exploration
  bt_t root_board;    // sauvegarde de l'état initial
  bt_t mcts_board;    // position courante pendant la descente
  std::unordered_map<std::string, int> H; // table de transposition
  bt_node_t* T;       // racine de l'arbre UCT

  int player_color;
  
  bt_tree_t(int _nb_nodes_alloc, int _descent_alloc, bt_t _root_board, int _pcolor) {
    root_board = _root_board;
    nb_nodes_alloc = _nb_nodes_alloc;
    descent_alloc = _descent_alloc;
    T = new bt_node_t[nb_nodes_alloc];
    descent_pid = new int[descent_alloc];
    descent_cid = new int[descent_alloc];
    root_board.update_moves();
    T[0].infos.resize(root_board.nb_moves);
    for(int i = 0; i < root_board.nb_moves; i++) {
      T[0].infos[i].move = root_board.moves[i];
    }
    nb_nodes = 1;
    player_color = _pcolor;
  }
  ~bt_tree_t() {
    delete[] T;
    delete[] descent_pid;
    delete[] descent_cid;
  }
  void print(int _id) {
    printf("node %p N: %d nb_terminal: %d\n", &T[_id], T[_id].N, T[_id].nb_terminal);
    for(bt_node_info_t i : T[_id].infos) { printf("  "); i.print(); }
  }
  void print_descent() {
    printf("descent :\n");
    for(int i = 0;i < descent_size; i++) printf("(%d %d) ", descent_pid[i], descent_cid[i]);
  }
  void selection() {
    while(true) {
      mcts_board = root_board;
      descent_size = 0;
      if(selection_expansion(0, 0)) break;
    }
  }
  bool selection_expansion(int _node_id, int _depth) {
    // si complètement exploré en passant par un autre chemin
    if(T[_node_id].nb_terminal == (int)T[_node_id].infos.size()) {
      T[descent_pid[_depth-1]].infos[descent_cid[_depth-1]].terminal = true;
      T[descent_pid[_depth-1]].nb_terminal ++;
      descent_size = _depth;
      return false;
    }
    // profondeur max atteinte
    if(_depth >= descent_alloc) {
      printf("ERROR : _depth %d >= descent_alloc in selection %d\n", _depth, descent_alloc); exit(0);
    }
    // on note le nœud courant
    descent_pid[_depth] = _node_id;
    descent_cid[_depth] = -1;
    // on sélectionne le meilleur enfant (non complètement exploré)
    int best_id = 0;
    double best_score = 0.0;
    bool all_terminal = true;
    int nb_Wi_null = 0;
    int random_base = 0;
    for(int i = 0; i < (int)T[_node_id].infos.size(); i++) {
      if(T[_node_id].infos[i].Ni == 0) {
	nb_Wi_null ++;
      } else {
	if(nb_Wi_null == 0) {
	  if(T[_node_id].infos[i].terminal == false) {
	    all_terminal = false;
	    double my_Wi;
	    int my_Ni = T[_node_id].infos[i].Ni;
	    if((_depth%2) == 0) {
	      my_Wi = (double) T[_node_id].infos[i].Wi;
	    } else {
	      my_Wi = (double) (T[_node_id].infos[i].Ni-T[_node_id].infos[i].Wi);
	    }
	    double a = my_Wi/my_Ni;
	    double b = sqrt(log((double) T[_node_id].N) / my_Ni);
	    double score = a + K_UCT * b;
	    if(score > best_score) {
	      best_id = i;
	      best_score = score;
	    }
	  }
	}
      }
    }
    if(nb_Wi_null > 0) {
      int rmove = ((int)rand())%nb_Wi_null;
      int expansion_id = 0;
      for(int i = 0; i < (int)T[_node_id].infos.size(); i++) {
	if(T[_node_id].infos[i].Ni == 0) {
	  if(rmove == 0) {
	    expansion_id = i; break;
	  }
	  rmove--;
	}
      }
      mcts_board.play(T[_node_id].infos[expansion_id].move);
      descent_cid[_depth] = expansion_id;
      descent_size = _depth+1;
      return true;
    } else {
      descent_cid[_depth] = best_id; // on note l'enfant sélectionné
      //tous les enfants sont complètement explorés, le parent devrait être marqué
      if(all_terminal) {
	printf("ERROR selection all_terminal %d %d %d\n", _node_id, T[_node_id].nb_terminal, (int)T[_node_id].infos.size()); exit(0);
      }
      // on joue le coup pour passer à la position suivante
      mcts_board.play(T[_node_id].infos[best_id].move);
      std::string strboard =  mcts_board.mkH(); // calcul du hash de la position
      // recherche de la position dans la table de transpositions
      std::unordered_map<std::string, int>::iterator ii = H.find(strboard);
      if(ii != H.end()) { // on ajoute le noeud dans le H
	return selection_expansion(ii->second, _depth+1); // on continue la descente
      } else {
	int new_node_id = nb_nodes;
	T[new_node_id].infos.resize(mcts_board.nb_moves); // initialisation
	for(int i = 0; i < mcts_board.nb_moves; i++) {
	  T[new_node_id].infos[i].move = mcts_board.moves[i];
	}
	H[strboard] = new_node_id;       // on place le nœud dans la table de transpo
	nb_nodes++;                      // on prépare l'id pour le prochain nœud
	return selection_expansion(new_node_id, _depth+1);
      }
    }
    return true;
  }
  double simulation() {
    int selection_id = descent_pid[descent_size-1];
    int expansion_id = descent_cid[descent_size-1];
    // si la position est terminale, on note directement (pas de nœud créé)
    if(mcts_board.terminal() != EMPTY) {
      if(T[selection_id].infos[expansion_id].terminal == false) {
	T[selection_id].nb_terminal ++;
	T[selection_id].infos[expansion_id].terminal=true;
      }
      return mcts_board.score(player_color); // retourne le score dans la feuille
    }
    // sinon on fait un playout et on retourne le score
    mcts_board.playout();
    return mcts_board.score(player_color);
  }
  void backpropagate(double _score) {
    // on remonte chaque nœud
    for(int i = descent_size-1; i >= 0; i--) {
      int selection_id = descent_pid[i];
      int expansion_id = descent_cid[i];
      // on augmente le nombre de visites du parent et enfant
      T[selection_id].N ++;
      T[selection_id].infos[expansion_id].Ni ++;
      // si tous les enfants sont terminaux, on remonte l'info
      if(T[selection_id].nb_terminal == (int)T[selection_id].infos.size()) {
        if(i == 0) {
          printf("[backpropagate] problem WITHOUT SOLUTION ?\n");
          exit(0);
        }
        int prev_selection_id = descent_pid[i-1];
        int prev_expansion_id = descent_cid[i-1];
	if(T[prev_selection_id].infos[prev_expansion_id].terminal == false) {
	  T[prev_selection_id].nb_terminal ++;
	  T[prev_selection_id].infos[prev_expansion_id].terminal = true;
	}
      }
      if(_score == 1.0)
      	T[selection_id].infos[expansion_id].Wi ++;
    }
  }
  bt_move_t MCTS_UCT(int _seed, int _nb_playout) {
    srand(_seed);
    for(int i = 0; i < _nb_playout; i++) {
      selection();
      double score = simulation();
      backpropagate(score);
    }
    bt_move_t best_move;
    double best_val = 0;
    for(bt_node_info_t i : T[0].infos) {
      double val_i = ((double)i.Wi)/i.Ni;
      if(val_i > best_val) {
	best_val = val_i;
	best_move = i.move;
      }
    }
    return best_move;
  }
};
#endif /* MCTSBT_H */
