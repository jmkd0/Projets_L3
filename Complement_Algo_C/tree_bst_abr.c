#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tree{
    int data;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* create_abr_by_pre (int* preorder, int begin, int end){
	if (begin > end) return NULL;

    Tree* node = (Tree*)malloc(sizeof(Tree));
        node->data   = preorder[begin];
        node->left  = NULL;
        node->right = NULL;
	int i;
	for (i = begin; i <= end; i++) 
		if (preorder[i] > node->data) break;

	node->left  = create_abr_by_pre (preorder, begin + 1, i - 1);
	node->right = create_abr_by_pre (preorder, i, end);
	return node;
}
Tree* create_abr_by_pos (int* postorder, int begin, int end){
	if (begin > end) return NULL;

     Tree* node = (Tree*)malloc(sizeof(Tree));
        node->data   = postorder[end];
        node->left  = NULL;
        node->right = NULL;
	int i;
	for (i = end; i >= begin; i--) 
		if (postorder[i] < node->data) break;

	node->right = create_abr_by_pos (postorder, i + 1, end - 1);
	node->left  = create_abr_by_pos (postorder, begin, i);
	return node;
}
Tree* LevelOrder(Tree *node , int data){ 
     if(node == NULL){     
        Tree* node = (Tree*)malloc(sizeof(Tree));
        node->data  = data;
        node->left  = NULL;
        node->right = NULL;
        return node; 
     } 
     if(data <= node->data) 
     node->left = LevelOrder(node->left, data); 
     else
     node->right = LevelOrder(node->right, data); 
     return node;      
} 
  
Tree* create_abr_by_level (Tree* node, int* arr, int n) { 
    if(n==0)return NULL; 
    int i=0;
  
    while(i<n){
        node = LevelOrder(node , arr[i]); 
        i++;
    }
        
      
    return node; 
} 
void create_abr_by_seq (Tree** tree, int value){
    if(!(*tree)){
        Tree* node = (Tree*)malloc(sizeof(Tree));
        node->left = NULL;
        node->right = NULL;
        node->data = value;
        *tree = node;
        return;
    }
    if(value < (*tree)->data)
        create_abr_by_seq (&(*tree)->left, value);
    else if(value > (*tree)->data)
        create_abr_by_seq (&(*tree)->right, value);
}

void Prefixe(Tree* tree){
	if(tree == NULL) return;
    printf("%d   ",tree->data);
	Prefixe(tree->left);
    
	Prefixe(tree->right);
}
int main(){
    int preorder[]  = {10, 5, 1, 7, 40, 50};  
    int postorder[] = {1, 7, 5, 50, 40, 10};  
    int level[]     = {10, 5, 40, 1, 7, 50};  
    int sequence[]  = {10, 40, 50, 5, 7, 1};  
    int size, i;
       printf("with Preorder:  ");
    size = sizeof(preorder)/sizeof(preorder[0]);
    Tree* treepre = create_abr_by_pre (preorder, 0, size-1);
    Prefixe (treepre);
        printf("\nwith Postorder: ");
    size = sizeof(postorder)/sizeof(postorder[0]);
    Tree* treepos = create_abr_by_pos (postorder, 0, size-1);
    Prefixe (treepos);
        printf("\nWith Level:     ");
    size = sizeof(level)/sizeof(level[0]);
    Tree* treelevel = NULL;
     treelevel = create_abr_by_level (treelevel, level, size); 
    Prefixe (treelevel);
        printf("\nWith Sequence:  ");
    size = sizeof(sequence)/sizeof(sequence[0]);
    Tree* treeseq = NULL;
    for(i=0; i<size; i++) create_abr_by_seq (&treeseq, sequence[i]); 
    Prefixe (treeseq);
    printf("\n");
    return 0;
}
