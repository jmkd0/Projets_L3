#include <stdio.h>
#include <stdlib.h>

typedef struct Liste{
    int valeur;
    struct Liste *suivant;
} Liste;

void AjoutDebut(Liste *liste,  int nouveau){
    //printf("%d  ", debut);
    Liste *element= (Liste*)malloc(sizeof(Liste));
    if(element==NULL) return;
    element->valeur = nouveau;
    element->suivant = liste->suivant;
    liste->suivant = element;
}
void Affichage(Liste *liste){
    while(liste!=NULL){
        printf("%d   ",liste->valeur);
        liste=liste->suivant;
    }
}

void main(){
    int i, data[]={45,58,76,19};
    int size = sizeof(data)/sizeof(int);
    Liste  *liste = &(Liste){0, NULL};;

    for(i=0; i< size; i++) AjoutDebut(liste, data[i]);

  Affichage(liste->suivant) ;
}
