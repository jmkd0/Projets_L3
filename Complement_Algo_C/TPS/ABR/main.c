#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct Tree{
    int data;
    struct Tree *left;
    struct Tree *right;
} Tree;

/* Exercice 4: Research in a tree*/
Tree* research (Tree* tree, int data){
    if(tree == NULL || tree->data == data) return tree;
    if(data < tree->data) research (tree->left, data);
    else research (tree->right, data);
}
/* Exercice 5: Insert in a tree  */
void insert (Tree** tree, int value){
    if(!(*tree)){
        Tree* node = (Tree*)malloc(sizeof(Tree));
        node->left = NULL;
        node->right = NULL;
        node->data = value;
        *tree = node;
        return;
    }
    if(value < (*tree)->data)
        insert (&(*tree)->left, value);
    else if(value > (*tree)->data)
        insert (&(*tree)->right, value);
}
/* Exercice 6: Delete in a tree */
Tree* delete_node (Tree* tree, int data){
    if(tree == NULL) return tree;
    if(data < tree->data) tree->left  = delete_node (tree->left, data);
    else if(data > tree->data) tree->right = delete_node (tree->right, data);
    else{//tree->data == data
        if(tree->left == NULL){ //no left child
            Tree* node = tree->right;
            free(tree);
            return node;
        }else
        if(tree->right == NULL){ //no right child
            Tree* node = tree->left;
            free(tree);
            return node;
        }else{
        //node with two child
        Tree* node = tree->right;
        while(node != NULL && node->left != NULL) node = node->left;//search the next inorder in the right tree
        tree->data = node->data; //swap the two content 
        tree->right = delete_node (tree->right, node->data);//delete in right tree the next inorder
        }
    }
    return tree;
}
/* Exercice 6: Delete bigger */
Tree* delete_node_big (Tree* tree){
    if(tree == NULL) return tree;
    Tree* node = tree->right;
    while(node != NULL && node->right->right != NULL) node = node->right;//search the last inorder 
        if(node->right->left != NULL){
            Tree* temp = node->right->left;
            free(temp->right);
            node->right = temp;
        }else{
            free(node->right->right);
            node->right = NULL;
        } 
    return tree;
}
/* Exercice 6: Delete smaller */
Tree* delete_node_small (Tree* tree){
    if(tree == NULL) return tree;
    Tree* node = tree->left;
    while(node != NULL && node->left->left != NULL) node = node->left;//search the last inorder 
        if(node->left->right != NULL){
            Tree* temp = node->left->right;
            free(temp->left);
            node->left = temp;
        }else{
            free(node->left->left);
            node->left = NULL;
        }
    return tree;
}
//EXERCICE 8
//Compare two trees
int  compare_tree (Tree* tree1, Tree* tree2){
	if(tree1 == NULL && tree2 == NULL) return 1;
    else if(tree1 != NULL && tree2 == NULL) return 0;
    else if(tree1 == NULL && tree2 != NULL) return 0;
    else if(tree1->data == tree2->data && compare_tree(tree1->left, tree2->left) && 
    compare_tree(tree1->right, tree2->right)) return 1;
    else return 0;
}
//EXERCICE 9
//Test of Binary tree search
int test_search_tree (Tree* tree){
    int static min = INT_MIN;
    if(tree == NULL) return 1;
    if(!(test_search_tree(tree->left))) return 0;
    if(min > tree->data) return 0;
    min = tree->data;

	return test_search_tree(tree->right);
}

void Prefixe(Tree* tree){
	if(tree == NULL) return;
    printf("%d   ",tree->data);
	Prefixe(tree->left);
    
	Prefixe(tree->right);
}
int main(){
    int sequence[]  = {8, 9, 5, 11, 0, 6, 10, -1, 1, 2}; 
    int sequence1[]  = {8, 9, 5, 11, 0, 6, 10, -1, 1, 2}; 
    int size = sizeof(sequence)/sizeof(sequence[0]);

    //EXERCICE 5
       /* Insert in a tree */
    Tree* tree = NULL;
    Tree* tree1 = NULL;
    for(int i=0; i < size; i++) insert (&tree, sequence[i]);
    for(int i=0; i < size; i++) insert (&tree1, sequence1[i]);
    printf("Exercice 5:\nTPreorder after insertion:\n");
    Prefixe (tree);

    //EXERCICE 4
        /* Rechercher */
    Tree* seek = research(tree, 6);
    printf("\n\nExercice 4:\nTThe serached value is:  %d",seek->data);
    
    //EXERCICE 6
        /* Delete a node in a tree */
    tree = delete_node (tree, -1);
    printf("\n\nExercice 6:\nTPreorder after deletion of -1:\n");
    Prefixe (tree);

    //EXERCICE 7
    /* Delete biggest node in a tree */
    tree = delete_node_big (tree);
    printf("\n\nExercice 7:\nTPreorder after deletion of heighest node:\n");
    Prefixe (tree);

    /* Delete smallest node in a tree */
    tree = delete_node_small (tree);
    printf("\n\nPreorder after deletion of smallest node:\n");
    Prefixe (tree);

    //EXERCICE 8
    /* Compare two trees  */
    int test = compare_tree (tree, tree);
    printf("\n\nExercice 8:\nCompare the two trees:\n");
    if(test == 0){
          printf("False: Those trees are not same");
    }else printf("True: Those trees are same");

    //EXERCICE 9
    /* Check whether a binary tree is a tree search  */
    test = test_search_tree (tree);
    printf("\n\nExercice 9:\nTest of binary tree search:\n");
    if(test == 0){
          printf("Fase: This tree is not a binary tree search");
    }else printf("True: This tree is a binary tree search");
    printf("\n");
    return 0;
}