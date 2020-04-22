#ifndef __IRIS__H_
#define __ISIS__H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>
struct Size{
    int     columnIris;
    int     lineIris;
    int     nbreNeuronne;
    int     vertical;
    int     horizontal;
    int     ordonnencement;
    int     affinage;
    int     voisinage;
    double  alpha_ordonn;
    double  alpha_affin;
}size = {.vertical=6, .ordonnencement=500, .affinage=1500, .alpha_ordonn=1, .alpha_affin=1}; 

char* categories[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

typedef struct{
    double*     dataIris;
    double*     normalized;
    char*       nameIris;
}DataIris;

typedef struct{
    double*     average;
    int**       result;
    double***   neuronne;
}DataNeuronne;

typedef struct{
    double  distance_to_the_bmu;
    int     i_bmu;
    int     j_bmu;
}BestMatchUnit;





//Function to find the size (line and column ) of datas in database
void SetSizeDataIris (char* fileName){
    int     line = 0, column = 0;
    char*   chaine; 
    int     lineSize = 100;
    char*   ligne = (char*) malloc(lineSize * sizeof(char));
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
    size.horizontal = size.nbreNeuronne / size.vertical;
    //Calculate the "voisinage" contening the 50% neuronne
    int k = 1;
    while (pow(2 * k + 1, 2) -1 < (int)(size.vertical * size.horizontal / 2)) k ++;
    size.voisinage = k;
}
//Function to reserve space for DataIris
DataIris* reserveSpaceDataIris (DataIris* data){
    data = malloc (size.lineIris * sizeof(DataIris));
    for(int i=0; i< size.lineIris; i++){
        data[i].dataIris = (double*) malloc (size.columnIris * sizeof(double));
        data[i].normalized = (double*) malloc (size.columnIris * sizeof(double));
        
    }
    return data;
}
//Function to reserve space for DataNeuronne
DataNeuronne* reserveSpaceDataNeuronne (DataNeuronne* dataNeuronne){
    dataNeuronne = ( DataNeuronne* )malloc( sizeof( DataNeuronne ));
    dataNeuronne->average =  (double*) malloc (size.columnIris * sizeof(double));

    dataNeuronne->result =  (int**) calloc ( size.vertical, sizeof(int*));
    dataNeuronne->neuronne =  (double***) malloc (size.vertical * sizeof(double**));
    
    for(int i=0; i< size.vertical; i++){
        dataNeuronne->result[i] = (int*) calloc ( size.horizontal, sizeof(int));
        dataNeuronne->neuronne[i] = (double**) malloc (size.horizontal * sizeof(double*));
        for(int j=0; j< size.horizontal; j++){
            dataNeuronne->neuronne[i][j] = (double*) malloc (size.columnIris * sizeof(double));
        }
    }
    
    
    return dataNeuronne;
}
//Function to charge all datas from the database
DataIris * ChargeDatabase(char* fileName, DataIris *data){
    int     lineSize = 100;
    char*   ligne = (char*)malloc(lineSize*sizeof(char));
    char*   chaine;   
    int     compterLine=0, compterColonne;
    FILE* fichier = fopen(fileName, "r");
    if (fichier != NULL){
        while ( fgets( ligne, lineSize, fichier) != NULL ){
            compterColonne = 1;
            chaine=strtok(ligne, ",");
            data[compterLine].dataIris[0] = atof(chaine);
            while(compterColonne < size.columnIris){
                chaine=strtok(NULL, ",");
                data[compterLine].dataIris[compterColonne] = atof(chaine);
                compterColonne++;
            }
            chaine=strtok(NULL, "\n");
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
    norme = 0;
        for(j= 0; j < colonne; j++)
                norme += pow(data[i].dataIris[j],2);
        norme = sqrt(norme);
        
    for(i=0; i< ligne; i++){
        /* norme = 0;
        for(j= 0; j < colonne; j++)
                norme += pow(data[i].dataIris[j],2);
        norme = sqrt(norme); */
        for(j=0; j< colonne; j++)
            data[i].normalized[j] = data[i].dataIris[j]/norme;
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
            mean += data[i].normalized[j];
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
        minimum = dataNeuronne->average[k] - 0.1;//0.05;
        maximum = dataNeuronne->average[k] + 0.1;//0.025;
       for(int i=0; i< size.vertical; i++){
            for(int j=0; j< size.horizontal; j++){
                dataNeuronne->neuronne[i][j][k] = (rand()/(double)RAND_MAX)*(maximum-minimum)+minimum;
            }
        }         
    }
    return dataNeuronne;
} 



#endif