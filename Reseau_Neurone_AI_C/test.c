#include <stdio.h>
typedef struct Etude{
    int tab[2][2];
}Etude;
 void displaytab (int *tab){
    int j;
    for(j=0; j<2; j++){
            printf("%d ", tab[j]);
    }
} 

int main(){
    int i,j;
    Etude Mat;
    Mat.tab[0][0]=1;Mat.tab[0][1]=2;
    Mat.tab[1][0]=3; Mat.tab[1][1]=5;
    for(i=0; i<2; i++){
        displaytab (Mat.tab[i]);
        printf("\n");
    } 
    return 0;
}