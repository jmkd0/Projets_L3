#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct List{
    int  size;
    Node *begin;
    Node *end;
}List;

void addBack (List* list, int data){
    Node* node= (Node*)malloc(sizeof(Node));
    node->data = data;
    if(list->begin == NULL){
        list->begin = node;
        list->end   = node;
        list->size++;
        return;
    }
    list->end->next = node;
    node->prev = list->end;
    list->end = node;
    list->size++;
}
void addFront (List* list, int data){
    Node* node= (Node*)malloc(sizeof(Node));
    node->data = data;
    if(list->begin == NULL){
        list->begin = node;
        list->end   = node;
        list->size++;
        return;
    }
    node->next = list->begin;
    node->prev = NULL;
    list->begin->prev = node;
    list->begin = node;
    list->size++;
}
int eraseFront(List* list){
    Node* node = list->begin;
    if(node == NULL) exit(0);
     list->begin = node->next;
     list->size--;
     if(node->next != NULL)
     node->next->prev = NULL;
    int front = node->data;
    free(node);
    return front;
}
int eraseBack(List* list){
    Node* node = list->end;
    if(node == NULL) exit(0);
     list->end = node->prev;
     list->size--;
     if(node->prev != NULL)
        node->prev->next = NULL;
    int back = node->data;
    free(node);
    return back;
}
void display(List* list){
    Node* tmp = list->begin;
    while(tmp != NULL){
        printf("%d   ",tmp->data);
        tmp = tmp->next;
    }
    tmp = list->end; printf("\n");
    while(tmp != NULL){
        printf("%d   ",tmp->data);
        tmp = tmp->prev;
    }
}

int main() {
    int i, data[]={5,8,9,4,45,58,76,19};
    int size = sizeof(data)/sizeof(int);
    List *list = &(List){0, NULL, NULL};
    
    for(i=0; i< 4; i++) addFront(list,data[i]); //4 9 8 5
    for(i=4; i< size; i++) addBack(list,data[i]); //45 58 76 19
    
    display (list);
    printf("\nSize: %d\n",(int)list->size);
    

    int front = eraseFront(list);
    printf("\nCancel front: %d\n", front);
    
    int back = eraseBack(list);
    printf("\nCancel back: %d\n", back);
    
    display (list);
    printf("\nSize: %d\n",(int)list->size);
    return 0;
}