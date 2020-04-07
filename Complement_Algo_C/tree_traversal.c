#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tree{
    char data;
    struct Tree *left;
    struct Tree *right;
} Tree;

typedef struct List{
    Tree* tree;
    struct List *next;
} List;

Tree* create_tree(Tree* left, Tree* right, char data){
	Tree* node = (Tree*)malloc(sizeof(Tree));
	if(node == NULL) return NULL;
	node->data = data;
	node->left = left;
	node->right = right;
	return node;
}

void Prefixe(Tree* tree){
	if(tree == NULL) return;
	printf("%c   ",tree->data);
	Prefixe(tree->left);
	Prefixe(tree->right);
}
void Infixe(Tree* tree){
	if(tree == NULL) return;
	Infixe(tree->left);
	printf("%c   ",tree->data);
	Infixe(tree->right);
}
void Postfixe(Tree* tree){
	if(tree == NULL) return;
	Postfixe(tree->left);
	Postfixe(tree->right);
	printf("%c   ",tree->data);
}
void addBack (List* list, Tree* tree){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    List* end = list;
    while(end->next != NULL) end =end->next;
    node->tree = tree;
    node->next = NULL;
    end->next = node;
}

Tree* eraseFront (List* list){
     List* first = list->next;
    if ( first == NULL) exit( EXIT_FAILURE) ;
    Tree* front = first->tree;
    list->next = list->next->next;
    free(first);
   return front;
}

void parcoursLargeur (Tree* tree){
    if( tree == NULL) return;
    List  *file = &(List){NULL, NULL};
    addBack (file, tree);
    while( file->next != NULL){
        Tree* node = eraseFront( file );
        printf("%c   ", node->data);
        if( node->left != NULL) addBack (file, node->left);
        if( node->right != NULL) addBack (file, node->right);
    }
}
void main(){
    Tree* F = create_tree (NULL,NULL,'F');
	Tree* E = create_tree (NULL,NULL,'E');
	Tree* D = create_tree (NULL,NULL,'D');
	Tree* C = create_tree (NULL,F,   'C');
	Tree* B = create_tree (D,   E,   'B');
	Tree* A = create_tree (B,   C,   'A');

        printf("Prefixe:\n");
    Prefixe(A);
        printf("\nInfixe:\n");
    Infixe(A);
        printf("\nPostfixe:\n");
    Postfixe(A);
        printf("\nLargeur\n");
    parcoursLargeur (A);
    printf("\n");
}
