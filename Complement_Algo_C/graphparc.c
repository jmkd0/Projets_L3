#include <stdio.h>
#include <stdlib.h>

typedef enum {
    false,
    true
} Bool;

typedef struct Node_List{
    int    value;
    struct Node_List *next;
} Node_List;

typedef struct Sommet_List{
    Node_List  *begin;
}Sommet_List;

typedef struct Graph{
    int         nbre_sommet;
    Bool        oriented;
    Sommet_List *sommet_list; 
}Graph;

typedef struct Link{
    int src;
    int dest;
} Link;

Graph *new_Graph ( int nbre_sommet, Bool oriented ) {
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    graph->nbre_sommet = nbre_sommet;
    graph->oriented = oriented;
    graph->sommet_list = (Sommet_List*) malloc( nbre_sommet*sizeof(Sommet_List));
    return graph;
}

void add_Node( Graph *graph, int src, int dest){

    Node_List *node = (Node_List*)malloc(sizeof(Node_List));
    node->value = dest;
    node->next = graph->sommet_list[src].begin;
    graph->sommet_list[src].begin = node;

    if( !graph->oriented){
        node = (Node_List*)malloc(sizeof(Node_List));
        node->value = src;
        node->next = graph->sommet_list[dest].begin;
        graph->sommet_list[dest].begin = node;
    }
}

void display_Graph ( Graph *graph, char *data ){
    int i;
    if (graph == NULL) return;
    for (i = 0; i < graph->nbre_sommet; i++){
        Node_List *node = graph->sommet_list[i].begin;
        printf("%c", data[i]);
        while (node != NULL){
            printf (" => %c",data[node->value]);
            node = node->next;
        }
        printf (" => NULL\n");
    }
}

int main(){
    int i;
    char data[]={'A', 'B', 'C', 'D', 'E'};
    Link link[]={{0,1}, {2,4}, {3,4}, {0,2}, {2,3}, {0,3}};

    int nbre_link = sizeof(link)/sizeof(link[0]);
    int nbre_node = sizeof(data)/sizeof(data[0]);

    Graph *graph = new_Graph(nbre_node,false);
    
    for(i = 0; i < nbre_link; i++)  add_Node (graph, link[i].src, link[i].dest);

    display_Graph (graph, data);
    return 0;
}