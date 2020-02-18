#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int main(){
    srand(time(NULL));
    int Rand[10];
    int i, t, a=0, b=10;
    int random;
    for( i=0; i<b; i++) Rand[i] = i;
    for( i= 0; i<b; i++){
        random = rand()%(b-a)+a;
        t= Rand[i];
        Rand[i]=Rand[random];
        Rand[random]=t;
    }
    for( i=0; i<b; i++) printf("%d ", Rand[i]);

    return 0;
}