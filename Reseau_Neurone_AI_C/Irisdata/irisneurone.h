#ifndef __IRIS__H_
#define __ISIS__H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>
struct Size{
    int columnIris;
    int lineIris;
    int nbreNeuronne;
    int horizontal;
    int vertical;
}size = {0, 0, 0, 4, 0}; 

typedef struct{
    double* dataIris;
    double* normalizeDataIris;
    char*  nameIris;
    double distance_to_the_bmu;
    int     i_bmu;
    int     j_bmu;
}DataIris;

typedef struct{
    double* average;
    DataIris** neuronne;
}DataNeuronne;

//Function to find the size (line and column ) of datas in database
void SetSizeDataIris (char* fileName){
    int line = 0, column = 0;
    char *chaine; 
    int lineSize = 100;
    char* ligne = (char*) malloc(lineSize * sizeof(char));
    //Column size
    FILE* fichier = fopen(fileName, "r");
    if (fichier != NULL)
        if(fgets( ligne, lineSize, fichier) != NULL){
            chaine=strtok(ligne, ",");
            while(chaine != NULL){
                column++;
                chaine=strtok(NULL, ","); 
            }
            size.columnIris = column -1;
        }
    //Line Size
    if (fichier != NULL){
        while ( fgets( ligne, lineSize, fichier) != NULL ) line++;
        size.lineIris = line+1;
    }
    fclose( fichier ) ;
    //Nombre neuronne
    size.nbreNeuronne = (int)(5 * sqrt(size.lineIris));
    size.vertical = size.nbreNeuronne / size.horizontal;
}
//Function to reserve space for DataIris
DataIris* reserveSpaceDataIris (DataIris* data){
    data = malloc (size.lineIris * sizeof(DataIris));
    for(int i=0; i< size.lineIris; i++){
        data[i].dataIris = (double*) malloc (size.columnIris * sizeof(double));
        data[i].normalizeDataIris = (double*) malloc (size.columnIris * sizeof(double));
        
    }
    return data;
}
//Function to reserve space for DataNeuronne
DataNeuronne* reserveSpaceDataNeuronne (DataNeuronne* dataNeuronne){
    dataNeuronne = ( DataNeuronne* )malloc( sizeof( DataNeuronne ));
    dataNeuronne->average =  (double*) malloc (size.columnIris * sizeof(double));
    dataNeuronne->neuronne =  (DataIris**) malloc (size.horizontal * sizeof(DataIris));
    for(int i=0; i< size.horizontal; i++){
        dataNeuronne->neuronne[i] = (DataIris*) malloc (size.vertical * sizeof(DataIris));
        for(int j=0; j< size.columnIris; j++){
            dataNeuronne->neuronne[i][j].dataIris = (double*) malloc (size.columnIris * sizeof(double));
        }
    }
    return dataNeuronne;
}
//Function to charge all datas from the database
DataIris * ChargeDatabase(char* fileName, DataIris *data){
    int lineSize = 100;
    char* ligne = (char*)malloc(lineSize*sizeof(char));
    char *chaine;   
    int compterLine=0, compterColonne;
    FILE* fichier = fopen(fileName, "r");
    if (fichier != NULL){
        while ( fgets( ligne, lineSize, fichier) != NULL ){
            compterColonne = 0;
            chaine=strtok(ligne, ",");
            while(compterColonne < size.columnIris){
                data[compterLine].dataIris[compterColonne] = atof(chaine);
                chaine=strtok(NULL, ",");
                compterColonne++;
            }
            data[compterLine].nameIris  = strdup(chaine);
           compterLine++;  
    } 
    fclose( fichier ) ;
    }
    return data;
} 
//Function to normalize the datas
DataIris* NormalizeMatrix(DataIris *data, int ligne, int colonne){
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
    return data;
}
//Function to calculate the average of datas
 DataNeuronne* AverageMatrix(DataNeuronne* dataNeuronne, DataIris *data, int ligne, int colonne){
    double mean;
    int i,j;
    for(j=0; j< colonne; j++){
        mean=0;
        for(i=0; i< ligne; i++)
            mean += data[i].normalizeDataIris[j];
        mean /= ligne;
        dataNeuronne->average[j] = mean;
    }
    return dataNeuronne;
 }
 //Function to create random neuronne between the average
DataNeuronne* EnvDonneeNeuronne (DataNeuronne* dataNeuronne){
    srand(time(NULL));
    int i,j;
    double minimum, maximum;
    for(int k=0; k< size.columnIris; k++){
        minimum = dataNeuronne->average[k] - 0.005;
        maximum = dataNeuronne->average[k] + 0.002;
       for(int i=0; i< size.horizontal; i++){
            for(int j=0; j< size.vertical; j++){
                dataNeuronne->neuronne[i][j].dataIris[k] = (rand()/(double)RAND_MAX)*(maximum-minimum)+minimum;

            }
        }         
    }
    return dataNeuronne;
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
//Function to calculate the distance between two vector or datas
double distance_neuronne ( double *Tab1, double *Tab2, int ligne){
    int i;
    double distance = 0;
    for (i=0; i < ligne; i++)
        distance += pow (Tab1[i]-Tab2[i], 2);
    distance = sqrt (distance);
    return distance;
}

DataIris * Winners_Neuronnes ( DataIris *data, DataNeuronne* dataNeuronne ){
    double distance;
    int *Rand = Rand_Table ( size.lineIris );
    for(int k=0; k< size.lineIris; k++){
        data[Rand[k]].distance_to_the_bmu = DBL_MAX;
        for(int i=0; i< size.horizontal; i++){
             for(int j=0; j< size.vertical; j++){
                 distance = distance_neuronne (data[Rand[k]].normalizeDataIris, dataNeuronne->neuronne[i][j].dataIris, size.columnIris);
                 if(distance < data[Rand[k]].distance_to_the_bmu ){
                     data[Rand[k]].distance_to_the_bmu = distance;
                     data[Rand[k]].i_bmu = i;
                     data[Rand[k]].j_bmu = j;
                 } 
             }
         }
    }
   return data;
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
 void display_average ( DataNeuronne* dataNeuronne, int colonne){
    int i;
    printf("\nMoyenne des données:\n");
    for( i=0; i< colonne; i++){
            printf("%f  ", dataNeuronne->average[i]);
    }
    printf("\n");
}
void display_neuronne_space (DataNeuronne* dataNeuronne){
    printf("\nEspace de Neuronne:\n");
    for(int i=0; i< size.horizontal; i++){
         for(int j=0; j< size.vertical; j++){
             for(int k=0; k< size.columnIris; k++){
                 printf("%f ", dataNeuronne->neuronne[i][j].dataIris[k]);
             }
             printf("\t");
         }
         printf("\n");
     }         
} 

void display_winner_neuronne (DataIris* data){
    printf("\nWinner Neuronnes\n");
    for(int i=0; i< size.lineIris; i++){
        printf("Iris %d proche de Neuronne (%d,%d) avec distance: %f",i, data[i].i_bmu, data[i].j_bmu, data[i].distance_to_the_bmu);
        printf("\n");
    }
}

void freeSpace (DataIris* data, DataNeuronne* dataNeuronne){
    for(int i=0; i< size.lineIris; i++){
        free(data[i].dataIris);
        free(data[i].normalizeDataIris); 
    }
    free(data);
}
#endif