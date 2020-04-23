#ifndef __IRIS__H_
#define __ISIS__H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>

struct Size{
    int     columnIris;                                     /* taille de vecteur d'un iris: 4 */
    int     lineIris;                                      /* nombre totale d'iris:   150    */
    int     nbreNeuronne;                                 /* nombre de neuronne:   60       */
    int     vertical;                                    /* largeur de l'environnement: 6  */
    int     horizontal;                                     /* longeur de l'environnement: 10 */
    int     ordonnencement;                                /* itteration ordonnencement: 500 */
    int     affinage;                                     /* itteration affinage: 1500      */
    int     rayon;                                       /* rayon de voisinage: 3 au debut */
    double  alpha_ordonn;                                   /* alpha ordonnencement   */
    double  alpha_affin;                                   /* alpha affinage         */

}   size    =  {.vertical=6, .ordonnencement=500, .affinage=1500, .alpha_ordonn= 1, .alpha_affin = 0.07}; 

char*       categories[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};


typedef struct{
    double*     dataIris;                 /* contient les données brutes       */
    double*     normalized;              /* contient les données normalisées  */
    char*       nameIris;               /* contient les noms des iris        */
}DataIris;

typedef struct{
    int**       result;                 /* contient les catégories de neuronne 1, 2, 3 */
    double***   neuronne;              /* contient l'espace de neuronne               */
}DataNeuronne;

typedef struct{
    double  distance;                   /* Best match Unit et sa distance */
    int     i;
    int     j;
}BMU;

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
    size.rayon = k;
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
void NormalizeMatrix(DataIris *data) {
	double norm = 0;
	for (int i = 0; i < size.lineIris; i++) {
		norm = 0;
        for(int j= 0; j < size.columnIris; j++)
                norm += pow(data[i].dataIris[j],2);
        norm = sqrt(norm);
		for (int j = 0; j < size.columnIris; j++) {
			data[i].normalized[j] = data[i].dataIris[j] / norm; 
		}
	}
}

//Function to calculate the average of datas
 double* AverageMatrix(DataIris *data){
    double* average =  (double*) malloc (size.columnIris * sizeof(double));
    double mean;
    for(int j=0; j< size.columnIris; j++){
        mean=0;
        for(int i=0; i< size.lineIris; i++)
            mean += data[i].normalized[j];
        mean /= size.lineIris;
        average[j] = mean;
    }
    return average;
 }

 //Function to create random neuronne between the average
DataNeuronne* EnvDonneeNeuronne (DataNeuronne* dataNeuronne, double* average){
    srand(time(NULL));
    double minimum, maximum;
    for(int k=0; k< size.columnIris; k++){
        minimum = average[k] - 0.05;
        maximum = average[k] + 0.025;
       for(int i=0; i< size.vertical; i++){
            for(int j=0; j< size.horizontal; j++){
                dataNeuronne->neuronne[i][j][k] = (rand()/(double)RAND_MAX)*(maximum-minimum)+minimum;
            }
        }         
    }
    return dataNeuronne;
} 

#endif