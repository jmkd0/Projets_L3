#ifndef TP4
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Tree4{
    int value;
    struct Tree4 *left;
    struct Tree4 *right;
} Tree4;

Tree4* create_perfect_tree_by_bfs(Tree4* tree, int i, int n) { 
    if (i < n) { 
        Tree4* node = (Tree4*)malloc(sizeof(Tree4)); 
        node->value = i; 
        node->left =  NULL;
        node->right = NULL;
        tree = node; 

        tree->left = create_perfect_tree_by_bfs(tree->left, pow(2, i), n); 
        tree->right = create_perfect_tree_by_bfs(tree->right, pow(2, i)+1, n); 
    } 
    return tree; 
} 
void Prefixe4(Tree4* arbre){
	if(arbre==NULL) return;
    printf("%d   ",arbre->value);
	Prefixe4(arbre->left);
	Prefixe4(arbre->right);
}
#endif