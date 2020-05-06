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
        if( node->left  != NULL) addBack (file, node->left);
        if( node->right != NULL) addBack (file, node->right);
    }
}
/* Research in a tree*/
Tree* research (Tree* tree, char data){
    static Tree* seek = NULL;
    if(tree == NULL) return NULL;
    if(tree->data == data) seek = tree;
    research (tree->left, data);
    research (tree->right, data);
    return seek;
}
/* Delete in a tree */
Tree* delete_node (Tree* tree, char data){
    if(tree == NULL) return tree;
    if(tree->data != data){
        tree->left  = delete_node (tree->left, data);
        tree->right = delete_node (tree->right, data);
    }else{//tree->data == data
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

    //Search in a tree
        printf("\nResearch");
    Tree* seek = research (A, 'E');
    if(seek != NULL) printf("\nThe searched value is: %c", seek->data);

    //Delete node in tree
        printf("\nPreorder after delete B\n ");
    Tree* treedelete = delete_node (A, 'B');
    Prefixe (treedelete);
    printf("\n");
}
