#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "exercices.h"

int main(){
    /*----------------------------EXERCICE 3---------------------------*/

    //char prefix[]={'A', 'B', 'D', 'G', 'H', 'E', 'I', 'C', 'F', 'J'};
    //char* prefix= "ABDGHEICFJ";
    //char prefix[]= "*+ab-cd";
    char prefix[]={'*', '+', 'a', 'b', '-', 'c', 'd'};
    char postfix[]={'a', 'b', '+', 'c', 'd', '-', '*'};
    
    Tree *tree = NULL;
    //printf("%d ", strlen(prefix));
    //create_tree_by_prefix (&tree, prefix );
    //create_tree_by_postfix (&tree, postfix );

        //Question 4
    char bfs[]={'H', 'I', 'D', 'J', 'K', 'E', 'B', 'L', 'F', 'G', 'C', 'A'};
    //Tree* treebfs = create_tree_by_bfs(treebfs, bfs, 0, sizeof(bfs)/sizeof(bfs[0])); 
    //Prefixe (treebfs);

    /*----------------------------EXERCICE 4---------------------------*/
    int height = 3;
    int node_number = pow(2, height+1)+5;
    Tree* treebin = create_perfect_tree_by_bfs(treebin, 1, node_number);
    

    /*----------------------------EXERCICE 5---------------------------*/
    //Question 1
    Prefixe (treebin);
    //Question 2
    parcoursLargeur ( treebin );
    printf(" \n");
    return 0;
}