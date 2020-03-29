#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tree{
    char data;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* create_tree_by_pre_in (char* preorder, char* inorder, int begin, int end, int *k){
    if (begin > end) return NULL;
    Tree* node = (Tree*)malloc(sizeof(Tree));
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
Tree* create_tree_by_pos_in (char* posorder, char* inorder, int begin, int end, int* k){
    if (begin > end) return NULL;
    Tree* node = (Tree*)malloc(sizeof(Tree));
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
Tree* create_tree_by_level_in(char* level, char* inorder, int begin, int end, int k) { 
    if (k <= 0) return NULL;
        Tree* node = (Tree*)malloc(sizeof(Tree)); 
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
void Prefixe(Tree* arbre){
	if(arbre==NULL) return;
    //printf("%c   ",arbre->data);
	Prefixe(arbre->left);
    printf("%c   ",arbre->data);
	Prefixe(arbre->right);
    //printf("%d   ",arbre->data);
}
void main(){
    char prefix[]=  {'A', 'B', 'D', 'E', 'C', 'F'}; 
    char postfix[]= {'D', 'E', 'B', 'F', 'C', 'A'};
    char level[]=   {'A', 'B', 'C', 'D', 'E', 'F'};
    char infix[]=   {'D', 'B', 'E', 'A', 'F', 'C'};  
   
    int size = sizeof(infix)/sizeof(infix[0]);
    int k = 0;
    Tree* nodepre = create_tree_by_pre_in (prefix, infix, 0, size-1, &k);
    Prefixe (nodepre);
        printf("\n");
    k = size -1;
    Tree* nodepos = create_tree_by_pos_in (postfix, infix, 0, size-1, &k);
    Prefixe (nodepos);
        printf("\n");
    k = size;
    Tree* nodelevel = create_tree_by_level_in(level, infix, 0, k-1, k); 
    Prefixe (nodelevel);
        printf("\n");
}
