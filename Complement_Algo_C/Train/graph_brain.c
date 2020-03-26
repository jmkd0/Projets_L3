#include <stdio.h>
#include <stdlib.h>
typedef enum {
    false,
    true
} Bool;

typedef struct Link{
    int src;
    int des;
}Link;

typedef struct Brin{
    int node;
    int sens;
} Brin;

typedef struct Graph_brin{
    int         nbre_sommet;
    int         *node;
    Brin        *next;
} Graph_brin;

Graph_brin *new_Graph ( int nbre_sommet, Bool oriented ) {
    Graph_brin *graph = (Graph_brin*) malloc(sizeof(Graph_brin));
    graph->nbre_sommet = nbre_sommet;
    graph->oriented = oriented;
    graph->sommet_list = (Brin*) malloc( nbre_sommet*sizeof(Brin));
    return graph;
}
void Insert( Graph_brin *graph, int sens, int node){
    
}
int main(){
    int i;
    char data[]={'A', 'B', 'C', 'D', 'E'};
    Link link[]={{0,1}, {2,4}, {3,4}, {0,2}, {2,3}, {0,3}};

    int nbre_link = sizeof(link)/sizeof(link[0]);
    int nbre_node = sizeof(data)/sizeof(data[0]);

    Graph_brin *graph = new_Graph(nbre_node,false);
    for(i=0; i<nbre_link; i++){
        Insert(graph, -(i+1), link[i].src);
        Insert(graph,  (i+1), link[i].des);
    }
    return 0;
}