#ifndef TP4
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Tree3{
    char data;
    struct Tree3 *left;
    struct Tree3 *right;
} Tree3;

typedef struct List{
    Tree3* tree;
    struct List *next;
} List;

//Creation d'arbre avec parcours Prefix
Tree3* create_tree_by_pre_in (char* preorder, char* inorder, int begin, int end, int *k){
    if (begin > end) return NULL;
    Tree3* node = (Tree3*)malloc(sizeof(Tree3));
        node->data   = preorder[*k];
        node->left  = NULL;
        node->right = NULL;
        (*k)++;
    if (begin == end) return node;
    int i, index;
    for (i = begin; i <= end; i++)
        if (inorder[i] == node->data) index = i;
    
    node->left = create_tree_by_pre_in (preorder, inorder, begin, index - 1, k);
    node->right = create_tree_by_pre_in (preorder, inorder, index + 1, end, k);
    return node;
}
//Creation d'arbre avec parcours Postfix
Tree3* create_tree_by_pos_in (char* posorder, char* inorder, int begin, int end, int* k){
    if (begin > end) return NULL;
    Tree3* node = (Tree3*)malloc(sizeof(Tree3));
        node->data   = posorder[*k];
        node->left  = NULL;
        node->right = NULL;
        (*k)--;
    if (begin == end) return node;
    int i, index;
    for (i = begin; i <= end; i++) 
        if (inorder[i] == node->data) index = i;
    
    node->right = create_tree_by_pos_in (posorder, inorder, index + 1, end, k);
    node->left = create_tree_by_pos_in (posorder, inorder, begin, index - 1, k);
    return node;
}
//Creation d'arbre avec parcours en largeur
Tree3* create_tree_by_level_in(char* level, char* inorder, int begin, int end, int k) { 
    if (k <= 0) return NULL;
        Tree3* node = (Tree3*)malloc(sizeof(Tree3)); 
        node->data = level[0]; 
        node->left =  NULL;
        node->right = NULL;
        int i, j, index;
        for (i = begin; i <= end; i++) 
            if (inorder[i] == node->data) index = i;

        char* inInorder = (char*)malloc((index-begin)*sizeof(char));
        for(i=0; i < index-begin; i++) inInorder[i]= inorder[begin+i];

        char*  leftLevel = (char*)malloc((index-begin)*sizeof(char));
        char* rightLevel = (char*)malloc((end-index)*sizeof(char));
        int l=0, r=0;
        for(i=1; i<k; i++){
            for (j=0; j<index-begin; j++)
                if(inInorder[j]==level[i]) break;
                
            if(j < index-begin) leftLevel[l++] = level[i];
                else rightLevel[r++]= level[i]; 
        }
        node->left  = create_tree_by_level_in(leftLevel, inorder, begin, index-1, index-begin); 
        node->right = create_tree_by_level_in(rightLevel, inorder, index+1, end, end-index); 
        free(inInorder); free(leftLevel); free(rightLevel);
    return node; 
} 
//Verification de sorties
//Fonction pour enfiler
void addBack (List* list, Tree3* tree){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    List* end = list;
    while(end->next != NULL) end =end->next;
    node->tree = tree;
    node->next = NULL;
    end->next = node;
}
//Fonction de défiler
Tree3* eraseFront (List* list){
     List* first = list->next;
    if ( first == NULL) exit( EXIT_FAILURE) ;
    Tree3* front = first->tree;
    list->next = list->next->next;
    free(first);
   return front;
}
void parcoursLargeur (Tree3* tree){
    if( tree == NULL) return;
    List  *file = &(List){NULL, NULL};
    addBack (file, tree);
    while( file->next != NULL){
        Tree3* node = eraseFront( file );
        printf("%c   ", node->data);
        if( node->left != NULL) addBack (file, node->left);
        if( node->right != NULL) addBack (file, node->right);
    }
}
void Prefixe(Tree3* arbre){
	if(arbre==NULL) return;
    printf("%c   ",arbre->data);
	Prefixe(arbre->left);
	Prefixe(arbre->right);
}
void Infixe(Tree3* arbre){
	if(arbre==NULL) return;
	Infixe(arbre->left);
    printf("%c   ",arbre->data);
	Infixe(arbre->right);
}
void Postfixe(Tree3* arbre){
	if(arbre==NULL) return;
	Postfixe(arbre->left);
	Postfixe(arbre->right);
    printf("%c   ",arbre->data);
}
int NombreNod(Tree3* arbre){
	if(arbre==NULL) return 0;
    static int nombre = 0;
    nombre++;
	NombreNod(arbre->left);
	NombreNod(arbre->right);
    return nombre;
}

#endif