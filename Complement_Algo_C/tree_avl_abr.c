#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tree{
    int data;
    int height;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* right_rotation (Tree* y){
    int left, right;
    Tree* x  = y->left;
    Tree* t2 = x->right;

    x->right = y;
    y->left  = t2;

    left  = (y->left == NULL)? 0 : y->left->height;
    right = (y->right == NULL)? 0 : y->right->height;
    y->height   = 1 + ((left > right)? left : right);

    left  = (x->left == NULL)? 0 : x->left->height;
    right = (x->right == NULL)? 0 : x->right->height;
    x->height   = 1 + ((left > right)? left : right);
    return x;
}

Tree* left_rotation (Tree* x){
    int left, right;
    Tree* y  = x->right;
    Tree* t2 = y->left;

    y->left  = x;
    x->right = t2;

    left  = (x->left == NULL)? 0 : x->left->height;
    right = (x->right == NULL)? 0 : x->right->height;
    x->height   = 1 + ((left > right)? left : right);

    left  = (y->left == NULL)? 0 : y->left->height;
    right = (y->right == NULL)? 0 : y->right->height;
    y->height   = 1 + ((left > right)? left : right);
    return y;
}

Tree* insert_tree (Tree* tree, int data){
    if(tree == NULL){
        Tree* tree   = (Tree*)malloc(sizeof(Tree));
        tree->data   = data;
        tree->left   = NULL;
        tree->right  = NULL;
        tree->height = 1;
        return tree;
    }//recherche de où ajouter
    if(data < tree->data) tree->left = insert_tree (tree->left, data);
    else if(data > tree->data) tree->right = insert_tree (tree->right, data);
    else return tree;

    int left  = (tree->left == NULL)? 0 : tree->left->height;
    int right = (tree->right == NULL)? 0 : tree->right->height;
    tree->height   = 1 + ((left > right)? left : right);

    int balance = left - right;
    //Left rotation
    if(balance > 1 && data < tree->left->data) return right_rotation (tree);
    //Left + Right rotation
    if(balance > 1 && data > tree->left->data){
        tree->left = left_rotation (tree->left);
        return right_rotation (tree);
    }
    //Right rotation
    if(balance < -1 && data > tree->right->data) return left_rotation (tree);
    //Right + Left rotation
    if(balance < -1 && data < tree->right->data){
        tree->right = right_rotation (tree->right);
        return left_rotation (tree);
    }
    return tree;
}

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
    if(tree == NULL) return tree;

    int left  = (tree->left == NULL)? 0 : tree->left->height;
    int right = (tree->right == NULL)? 0 : tree->right->height;
    tree->height   = 1 + ((left > right)? left : right);

    int balance = left - right;

    left  = (tree->left->left == NULL)? 0 : tree->left->left->height;
    right = (tree->left->right == NULL)? 0 : tree->left->right->height;
    //Left rotation
    if(balance > 1 && left - right >= 0) return right_rotation (tree);
    //Left + Right rotation
    if(balance > 1 && left - right < 0){
        tree->left = left_rotation (tree->left);
        return right_rotation (tree);
    }

    left  = (tree->right->left == NULL)? 0 : tree->right->left->height;
    right = (tree->right->right == NULL)? 0 : tree->right->right->height;
    //Right rotation
    if(balance < -1 && left - right <= 0) return left_rotation (tree);
    //Right + Left rotation
    if(balance < -1 && left - right > 0){
        tree->right = right_rotation (tree->right);
        return left_rotation (tree);
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
    int sequence[]  = {9, 5, 10, 0, 6, 11, -1, 1, 2};  
    //Tree avl
       printf("with Preorder:  ");
    int size = sizeof(sequence)/sizeof(sequence[0]);
    Tree* treepre = NULL;
    for(int i=0; i < size; i++) treepre = insert_tree (treepre, sequence[i]);
    Prefixe (treepre);
    printf("\n");
    treepre = delete_node (treepre, 10);
    Prefixe (treepre);
    printf("\n");

    return 0;
}
