#ifndef MYBT_H
#define MYBT_H
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    false,
    true
} Bool;

typedef struct Successor{
    int link;
    char   data;
    struct Successor *next;
} Successor;

typedef struct Graph{
    int         nbre_sommet;
    Bool        oriented;
    Successor *sommets; 
} Graph;

typedef struct Edge{
    int src;
    int dest;
} Edge;

Graph* new_Graph (char *datas, int nbre_sommet, Bool oriented ) {
    int i;
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    graph->nbre_sommet = nbre_sommet;
    graph->oriented = oriented;
    graph->sommets = (Successor*) malloc( nbre_sommet*sizeof(Successor));
     for(i=0; i<nbre_sommet; i++){
        graph->sommets[i].link = i;
        graph->sommets[i].data = datas[i];
        graph->sommets[i].next = NULL;
    } 
    return graph;
}

void add_Edge( Graph *graph, char *datas, int src, int dest){

    Successor *node = (Successor*)malloc(sizeof(Successor));
    node->link = dest;
    node->data = datas[dest];
    node->next = graph->sommets[src].next;
    graph->sommets[src].next = node;
    
    if( !graph->oriented){
        node = (Successor*)malloc(sizeof(Successor));
        node->link = src;
        node->data = datas[src];
        node->next = graph->sommets[dest].next;
        graph->sommets[dest].next = node;
    }
}

void display_Graph ( Graph *graph){
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
}

/* int main(){
    int i;
    char datas[]={'A', 'B', 'C', 'D', 'E'};
    Edge edge[]={{0,1}, {2,4}, {3,4}, {0,2}, {2,3}, {0,3}};

    int nbre_edge = sizeof(edge)/sizeof(edge[0]);
    int nbre_node = sizeof(datas)/sizeof(datas[0]);
    //Creation des noeuds
    Graph *graph = new_Graph(datas, nbre_node,false);
    //Creation des arrêtes
    for(i = 0; i < nbre_edge; i++)  add_Edge (graph, datas, edge[i].src, edge[i].dest);
    //Affichage
    display_Graph (graph);
    return 0;
} */
#endif /* MYBT_H */