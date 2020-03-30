#ifndef __IRIS__H_
#define __ISIS__H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define lineSize 100
#define nbreColonne 4
//Les trois elements suivant à modifier en changeant de base de donnée
#define nbreIris 150
#define nbreNeuronne 60
char* fileName = "iris.data"; /*https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data*/


typedef struct{
    double dataIris[nbreColonne];
    double normalizeDataIris[nbreColonne];
    char  nameIris[lineSize];
}DataIris;

typedef struct{
    double moyenne[nbreColonne];
    double neuronne[nbreNeuronne][nbreColonne];
}DataNeuronne;

void ChargeDatabase(DataIris *data, int colonne){
    FILE* fichier ;
    char ligne[lineSize];
    char *endValue=",";
    char *chaine;
    int compterLine=0, compterColonne;
    fichier= fopen(fileName, "r") ;
    if (fichier != NULL){
        while ( fgets( ligne, lineSize, fichier) != NULL ){
            compterColonne=0;
            chaine=strtok(ligne, endValue);
            while(compterColonne < colonne){
                data[compterLine].dataIris[compterColonne] = atof(chaine);
                chaine=strtok(NULL, endValue);
                compterColonne++;
            }
            strcpy(data[compterLine].nameIris, chaine);
           compterLine++;  
    } 
    fclose( fichier ) ;
    }
}
void NormalizeMatrix(DataIris *data, int ligne, int colonne){
    int i,j;
    double norme;
    for(i=0; i< ligne; i++){
        norme = 0;
        for(j= 0; j < colonne; j++)
                norme += pow(data[i].dataIris[j],2);
        norme = sqrt(norme);
        for(j=0; j< colonne; j++)
            data[i].normalizeDataIris[j] = data[i].dataIris[j]/norme;
    }
}
DataNeuronne* MoyenneMatrix(DataIris *data, int ligne, int colonne){
    DataNeuronne* dataNeuronne = ( DataNeuronne* )malloc( sizeof( DataNeuronne ));
    double mean;
    int i,j;
    for(j=0; j< colonne; j++){
        mean=0;
        for(i=0; i< ligne; i++)
            mean += data[i].normalizeDataIris[j];
        mean /= ligne;
        dataNeuronne->moyenne[j] = mean;
    }
    return dataNeuronne;
}
void EnvDonneeNeuronne (DataNeuronne* dataNeuronne, int ligne, int colonne){
    srand(time(NULL));
    int i,j;
    double minimum, maximum;
    for( j=0; j< colonne; j++){
        minimum = dataNeuronne->moyenne[j] - 0.005;
        maximum = dataNeuronne->moyenne[j] + 0.002;
        for( i=0; i< ligne; i++){
            dataNeuronne->neuronne[i][j] = (rand()/(double)RAND_MAX)*(maximum-minimum)+minimum;
        }
    }
}

/* Mise en place de tableau de valeurs aléatoires */

int* Rand_Table ( int b ){
    
    srand(time(NULL));
    int *Rand = (int*) malloc(b*sizeof(int));
    int i, random, t, a=0;
    for( i=0; i<b; i++) Rand[i] = i;
    for( i= 0; i<b; i++){
        random = rand()%(b-a)+a;
        t= Rand[i];
        Rand[i]=Rand[random];
        Rand[random]=t;
    }
    return Rand;
} 

double distance_neuronne ( double *Tab1, double *Tab2, int ligne){
    int i;
    double distance = 0;
    for (i=0; i < ligne; i++)
        distance += pow (Tab1[i]-Tab2[i], 2);
    distance = sqrt (distance);
    return distance;
}

void Winners_Neuronnes ( DataIris *data, DataNeuronne* dataNeuronne, int ligne_iris,  int ligne_neuronne, int colonne ){

    int i,j, i_winner;
    double distance, distance_0;

    int *Rand = Rand_Table ( ligne_iris );
    
    for (i=0; i < ligne_iris; i++){
        distance_0 = distance_neuronne (data[Rand[i]].normalizeDataIris, dataNeuronne->neuronne[0], colonne);
        //printf("Iris %d et neuronne %d ont pour distance:  %f\n",  Rand[i], 0, distance_0);
        for (j=1; j < ligne_neuronne; j++){
            distance = distance_neuronne (data[Rand[i]].normalizeDataIris, dataNeuronne->neuronne[j], colonne);
            //printf("Iris %d et neuronne %d ont pour distance:  %f\n", Rand[i], j, distance);
            if(distance < distance_0 ){
                distance_0 = distance;
                i_winner = j;
            } 
        }
        printf( "neunonne %d win iris %d proche de %f\n", i_winner, Rand[i],distance_0);
    }
}
//Displays
void display_database (DataIris *data, int ligne, int colonne ){
    int i,j;
    printf("Espace de données:\n");
    for( i=0; i< ligne; i++){
        for( j=0; j< colonne; j++){
            printf("%f  ", data[i].dataIris[j]);
        }
        printf("\n");
    }
}
void display_nameflower (DataIris *data, int ligne){
    int i;
     printf("\nNoms des fleurs:\n");
    for( i=0; i< ligne; i++){
            printf("%s", data[i].nameIris);
    }
    printf("\n");
}
void display_normalise (DataIris *data, int ligne, int colonne){
    int i,j;
    printf("\nDonnées Normalisées:\n");
    for( i=0; i< ligne; i++){
        for( j=0; j< colonne; j++){
            printf("%f  ", data[i].normalizeDataIris[j]);
        }
        printf("\n");
    }
}
void display_moyenne ( DataNeuronne* dataNeuronne, int colonne){
    int i;
    printf("\nMoyenne des données:\n");
    for( i=0; i< colonne; i++){
            printf("%f  ", dataNeuronne->moyenne[i]);
    }
    printf("\n");
}
void display_neuronne_space (DataNeuronne* dataNeuronne, int ligne, int colonne){
    int i,j;
    printf("\nEspace de Neuronne:\n");
     for( i=0; i< ligne; i++){
        for( j=0; j< colonne; j++){
            printf("%f  ", dataNeuronne->neuronne[i][j]);
        }
        printf("\n");
    } 
}

#endif