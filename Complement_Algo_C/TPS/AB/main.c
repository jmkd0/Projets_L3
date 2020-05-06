#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//pour exécuter : gcc -lm main.c
typedef struct Tree3{
    char data;
    struct Tree3 *left;
    struct Tree3 *right;
} Tree3;

typedef struct List{
    Tree3* tree;
    struct List *next;
} List;

typedef struct Tree4{
    int value;
    struct Tree4 *left;
    struct Tree4 *right;
} Tree4;


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