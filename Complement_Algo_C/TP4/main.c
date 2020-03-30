#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "exercice_a.h"
#include "exercice_b.h"
int main(){
    printf("----------------------------EXERCICE 3---------------------------\n\n");
    printf("\tQuestion 1: Parcours Prefix\n");
    char prefix1[]={'A', 'B', 'D', 'G', 'H', 'E', 'I', 'C', 'F', 'J'};
    char infix1[]={'D', 'B', 'H', 'G', 'E', 'A', 'C', 'I', 'J', 'F'}; //Afin d'avoir un arbre unique
    int size = sizeof(infix1)/sizeof(infix1[0]);
    int k = 0;
    Tree3* tree31 = create_tree_by_pre_in (prefix1, infix1, 0, size-1, &k);
    Prefixe (tree31);

    printf("\n\n\tQuestion 2: Parcours Infix\n");
    char prefix2[]={'F', 'B', 'A', 'D', 'C', 'E', 'H', 'G', 'I', 'J', 'K'};//Afin d'avoir un arbre unique
    char infix2[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'}; 
     size = sizeof(infix2)/sizeof(infix2[0]);
     k = 0;
    Tree3* tree32 = create_tree_by_pre_in (prefix2, infix2, 0, size-1, &k);
    Infixe (tree32);

    printf("\n\n\tQuestion 3: Parcours Postfix\n");
    char postfix3[]={'H', 'I', 'D', 'J', 'K', 'E', 'B', 'L', 'F', 'G', 'C', 'A'};
    char infix3[]=  {'H', 'J', 'I', 'D', 'E', 'K', 'A', 'B', 'C', 'L', 'G', 'F'}; //Afin d'avoir un arbre unique
     size = sizeof(infix3)/sizeof(infix3[0]);
     k = size -1;
    Tree3* tree33 = create_tree_by_pos_in (postfix3, infix3, 0, size-1, &k);
    Postfixe (tree33);

    printf("\n\n\tQuestion 4: Largeur\n");
    char largeur4[]={'H', 'I', 'D', 'J', 'K', 'E', 'B', 'L', 'F', 'G', 'C', 'A'};
    char infix4[]=  {'J', 'I', 'L', 'K', 'F', 'H', 'E', 'G', 'D', 'C', 'B', 'A'}; //Afin d'avoir un arbre unique
    size = sizeof(infix4)/sizeof(infix4[0]);
    k = size;
    Tree3* tree34 = create_tree_by_level_in(largeur4, infix4, 0, k-1, k); 
    parcoursLargeur (tree34);

    printf("\n\n----------------------------EXERCICE 4---------------------------\n\n");
    int height = 3;
    int node_number = pow(2, height+1)+5;
    Tree4* treebin = create_perfect_tree_by_bfs(treebin, 1, node_number);
    Prefixe4 (treebin);

    printf("\n\n----------------------------EXERCICE 5---------------------------\n\n");
    printf("confère le fichier exercice3.h qui contient les trois parcours\n");

    printf("\n\n----------------------------EXERCICE 6---------------------------\n\n");
    printf("\tQuestion 1: Nombre d'élément dans un arbre\n");
    int nombreNod = NombreNod(tree34);
    printf("Le nombre de noeud dans tree34 fait: N = %d noeuds",nombreNod);

  printf("\n");
    return 0;
}