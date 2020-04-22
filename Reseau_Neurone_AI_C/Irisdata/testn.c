#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
void eraseBack (List* list){
    List* last = list;
    if(list->next == NULL) exit( EXIT_FAILURE);
    while(last->next->next != NULL) last = last->next;
    free(last->next->next);
    last->next = NULL;
}
void display(List *list){
    list = list->next;
    while(list != NULL){
        printf("%d   ",list->value);
        list = list->next;
    }
}
void main(){
    int i, data[]={5,2,1,3, 9,0,1,58,1,19,1,2};
    int size = sizeof(data)/sizeof(int);
    List  *list = &(List){0, NULL};
    //for(i=0; i< size; i++) addBack(list, data[i]);
    //display(list) ;
    //int v=0;
    //while(list->next != NULL && v<3){ eraseBack (list); v++;}
    int petit = 100;
    for(i=0; i< size; i++){
        if(data[i] < petit ){
            petit = data[i];
            while(list->next != NULL) eraseBack (list); 
            addBack(list, i);
        }else if(data[i] == petit){
                addBack(list, i);
        }
    }
    int cpt = 0;
    List  *N = list;
    while(N->next != NULL) {
        cpt++;
        N = N->next;
    }
    srand(time(NULL));
    cpt = rand()%cpt+1;
    int pos=0;
    while(pos != cpt && list->next != NULL){ list = list->next; pos++;}
     printf("value =%d ",list->value);
     printf("\n");

  //display(list) ;//>>4 9 8 5 45 58 76 19 23

  /* //Erase Front
  int front = eraseFront (list);
  printf("\ncancel front %d\n ", front);
  display(list) ;//>>9 8 5 45 58 76 19 23
  //Erase End
  int back = eraseBack (list);
  printf("\ncancel back %d\n ", back);
  display(list) ;//>>9 8 5 45 58 76 19 */
  //printf("\n");
}
