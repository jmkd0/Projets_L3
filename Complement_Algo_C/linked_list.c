#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct List{
    int value;
    struct List *next;
} List;

void addFront(List *list,  int value){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    node->value = value;
    node->next = list->next;
    list->next = node;
}
void addBack (List* list, int value){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    List* end = list;
    while(end->next != NULL) end =end->next;
    node->value = value;
    node->next = NULL;
    end->next = node;
}

void addEnd1(List** end,  int value){
    List *node = (List*)malloc(sizeof(List));
    if(node == NULL) return;
    node->value = value;
    node->next = NULL;
    (*end)->next = node;
    *end = node;
}
 int eraseFront (List* list){
     List* first = list->next;
    if ( first == NULL) exit( EXIT_FAILURE) ;
    int front = first->value;
    list->next = list->next->next;
    free(first);
   return front;
}
int eraseBack (List* list){
    List* last = list;
    int back ;
    if(list->next == NULL) exit( EXIT_FAILURE);
    if(last->next->next == NULL) back = last->next->value;
    while(last->next->next != NULL) last = last->next;
    back = last->next->value;
    free(last->next->next);
    last->next = NULL;
  return back;
}
void display(List *list){
    list = list->next;
    while(list != NULL){ðb b
        printf("%d   ",list->value);
        list = list->next;
    }
}
void main(){
    int i, data[]={5,8,9,4,45,58,76,19};
    int size = sizeof(data)/sizeof(int);
    List  *list = &(List){0, NULL};
   
    for(i=0; i< 4; i++) addFront(list, data[i]); //4 9 8 5
    for(i=4; i< size; i++) addBack(list, data[i]);//45 58 76 19
    /*List  *end = list;
    addEnd1(&end, 23);*/

  display(list) ;//>>4 9 8 5 45 58 76 19 23

  //Erase Front
  int front = eraseFront (list);
  printf("\ncancel front %d\n ", front);
  display(list) ;//>>9 8 5 45 58 76 19 23
  //Erase End
  int back = eraseBack (list);
  printf("\ncancel back %d\n ", back);
  display(list) ;//>>9 8 5 45 58 76 19
  printf("\n");
}
