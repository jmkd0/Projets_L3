#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
typedef short unsigned Shu;
struct strand {
  Shu node;
  short next;
};
typedef struct strand strand;
struct strandgraph {
  Shu nbs;
  Shu nbstr;
  short * node; /* first strand*/
  strand * nxt;/* node and next strand*/
} ;
typedef struct strandgraph strgr;
void insert (strgr g, int num, Shu nod) {
  short first, second, adv;
  //printf("%d \n",g.nbstr);
  adv = g.nbstr >> 1;
  //printf("%d \n",adv);
  //printf("num %d nod %u first %d ", num, nod, g.node[nod]);
  
  //printf("next %d node %u\n",(g.nxt[num+adv]).next = num, (g.nxt[num+adv]).node = nod);
    //printf("%d \n",num);

  if (!g.node[nod]) {
      
	g.node[nod]=num;
	(g.nxt[num+adv]).next = num;
	(g.nxt[num+adv]).node = nod;
  }
  else {
	first  = g.node[nod];
	second = (g.nxt[first+adv]).next;
	(g.nxt[first+adv]).next = num;
	(g.nxt[num+adv]).next = second;
	(g.nxt[num+adv]).node = nod;
  }
  printf("first  %d ---------",g.node[nod]);
  printf("node  %u       next  %d  \n",(g.nxt[num+adv]).node, (g.nxt[num+adv]).next);
}
strgr transforme (Graph g) {
  Shu i;
  int nbstr, size_str, nbz;
  Successor* l;
  strgr newg;
  //nbstr = nonzeros (g);
  nbstr <<= 1;
  size_str = nbstr + 1;
  newg.nbs   = g.nbre_sommet;
  newg.nbstr = nbstr;
  //printf("%d \n\n",nbstr);
  newg.node  = (short *) malloc (g.nbre_sommet * sizeof(short));
  newg.nxt   = (strand *) malloc (size_str * sizeof(strand));
  memset(newg.node, 0, g.nbre_sommet* sizeof(short));
  for (i = 0, nbz = 1; i < g.nbre_sommet; i++) {
	l = g.sommets[i].next;
	while (l) {
	  insert(newg, -nbz, i);
	  insert(newg, nbz, l->link);
	  nbz++;
	  l = l->next;
	}
  }
  printf("on a %d brins\n", nbz);
  return newg;
}
/* void display_Brain ( strgr *graph){
    int i;
    if (graph == NULL) return;
    for (i = 0; i < graph->nbre_sommet; i++){
        Successor *node = &graph->sommets[i];
        while (node != NULL){
            printf (" %d =>", node->link);
            //printf (" %c =>", node->data);
            node = node->next;
        } 
        printf (" NULL\n");
    }
} */
int main(){
    int i;
    /* char datas[]={'A', 'B', 'C', 'D', 'E'};
    Edge edge[]={{0,1}, {2,4}, {3,4}, {0,2}, {2,3}, {0,3}}; */
    char datas[]={'A', 'B', 'C', 'D', 'E'};
    Edge edge[]={{0,3}, {1,2}, {4,1}, {4,0}, {0,1}};

    int nbre_edge = sizeof(edge)/sizeof(edge[0]);
    int nbre_node = sizeof(datas)/sizeof(datas[0]);
    //Creation des noeuds
    Graph *graph = new_Graph(datas, nbre_node,false);
    //Creation des arrêtes
    for(i = 0; i < nbre_edge; i++)  add_Edge (graph, datas, edge[i].src, edge[i].dest);
    //Affichage
    //display_Graph (graph);
    strgr Brain = transforme (*graph);
    //display_Brain(Brain);
    return 0;
}