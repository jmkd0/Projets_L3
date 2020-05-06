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
/* Create a tree with sequential insert  */
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
/* Research in a tree*/
Tree* research (Tree* tree, int data){
    if(tree == NULL || tree->data == data) return tree;
    if(data < tree->data) research (tree->left, data);
    else research (tree->right, data);
}

/* Delete in a tree */
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
    //Tree with Prefix
       printf("with Preorder:  ");
    size = sizeof(preorder)/sizeof(preorder[0]);
    Tree* treepre = create_abr_by_pre (preorder, 0, size-1);
    Prefixe (treepre);
    //Rechercher
    Tree* seek = research(treepre, 1);
        printf("\nThe serached value is %d",seek->data);
    //Delete node in tree
        printf("\nwith Preorder after delete 10: ");
    Tree* treedelete = delete_node (treepre, 10);
    Prefixe (treedelete);

    //Tree with Postfix
        printf("\nwith Postorder: ");
    size = sizeof(postorder)/sizeof(postorder[0]);
    Tree* treepos = create_abr_by_pos (postorder, 0, size-1);
    Prefixe (treepos);
    //Tree with Largeur
        printf("\nWith Level:     ");
    size = sizeof(level)/sizeof(level[0]);
    Tree* treelevel = NULL;
     treelevel = create_abr_by_level (treelevel, level, size); 
    Prefixe (treelevel);
    //Tree with Sequentiel
        printf("\nWith Sequence:  ");
    size = sizeof(sequence)/sizeof(sequence[0]);
    Tree* treeseq = NULL;
    for(i=0; i<size; i++) create_abr_by_seq (&treeseq, sequence[i]); 
    Prefixe (treeseq);

    printf("\n");
    return 0;
}
