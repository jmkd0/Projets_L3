#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* typedef struct Node{
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct List{
    int length;
    Node* begin;
    Node* end; 
}List; */
typedef struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
} Node;
typedef struct Node* List;
void addFront (List* list, int value){
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) return;
    node->next = node->prev = NULL;
    node->data = value;
    node->next = *list;
    if(*list != NULL) (*list)->prev = NULL;
    *list = node;
}
/* void addFront(List *list,  int value){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    node->value = value;
    node->prev = NULL;
    node->next = list->next;
    list->next = node;
} */
/* List* addBack (List* list, int value){
    Node *node= (Node*)malloc(sizeof(Node));
    if(node == NULL) exit(EXIT_FAILURE);
    node->value = value;
    if(list == NULL){
        list = (List*)malloc(sizeof(List));
        if(list == NULL) exit(EXIT_FAILURE);
        list->begin = node;
        list->end = node;
    }else{
        list->end->next = node;
        node->prev = list->end;
        list->end = node;
    }
   list->length++;
    return list;
} */
void display(List list){
    Node* temp = list;
    int i=0;
    while(temp != NULL){
        printf("%d   ",temp->data);
        if(i>1){
            printf("prev= %d ",temp->prev);
        }
        i++;
        temp = temp->next;
    } 
    printf("\n");
    //temp = temp->prev;
    //printf("%d   ",temp->data);
    //while(temp != NULL){
    //    printf("%d   ",temp->data);
    //    temp = temp->prev;
    //}
}
int main(){
    int i, datas[]={5,8,9,4,45,58,76,19};
    int size = sizeof(datas)/sizeof(int);
    List list = NULL;// &(List){0,NULL, NULL};
    //list->length = 5;
    //if(list->end != NULL)printf("%d ", list->length);
    for(i=0; i< 4; i++) addFront(&list, datas[i]); //4 9 8 5
    //for(i=4; i< size; i++){
    //    addBack(list, datas[i]);//45 58 76 19
    //} 
    display(list) ;
    return 0;
}