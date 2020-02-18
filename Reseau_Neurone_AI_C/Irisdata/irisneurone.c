#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "irisneurone.h"

void ChargeDatabase(DataIris *data, int colonne){
    FILE* fichier ;
    char ligne[lineSize];
    char *endValue=",";
    char *chaine;
    int compterLine=0, compterColonne;
    fichier= fopen("iris.data", "r") ;/*https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data*/
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