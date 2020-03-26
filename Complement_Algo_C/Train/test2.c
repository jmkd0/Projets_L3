#include <stdio.h>
#include <stdlib.h>

typedef struct Liste{
    int valeur;
    struct Liste *suivant;
} Liste;

void AjoutDebut(Liste *debut,  int nouveau){
    Liste *element= (Liste*)malloc(sizeof(Liste));
    if(element==NULL) return;
    debut->valeur = nouveau;
    debut->suivant = element;
    element= debut;
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

    /* Liste  init ={0, NULL};
    Liste  *liste = &init;
    Liste  *debut = liste; */
    Liste *liste = (Liste*)malloc(sizeof(Liste));
    Liste *debut = liste;

    for(i=0; i< size; i++) AjoutDebut(debut, data[i]);

  Affichage(liste) ;
}
