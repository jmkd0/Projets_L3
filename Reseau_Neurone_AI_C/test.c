#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    int val;
    char *nom;
    char name[10];
}Etude;
void modiff(Etude *etud){
     etud[0].val=19; etud[1].val=5; 
     etud[0].nom="jean"; etud[1].nom="koffi"; 
     strcpy(etud[0].name,"john");strcpy(etud[1].name,"koffa");
}

int main(){
    srand(time(NULL));
Etude etud[2];
int i;
double a=10.6, b=100.0; 
//Etude* etud=(Etude*)malloc(2*sizeof(Etude));
for(i=0; i<5; i++){
    printf("%f   "   ,(rand()/(double)RAND_MAX)*(b - a)+a);
}
    return 0;
}