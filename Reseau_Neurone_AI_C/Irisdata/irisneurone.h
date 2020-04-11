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
    int ordonnencement;
    int affinage;
    int voisinage;
    double alpha_ordonn;
    double alpha_affin;
}size = {.horizontal=6, .ordonnencement=500, .affinage=1500, .alpha_ordonn=0.9, .alpha_affin=0.07}; 

typedef struct{
    double* dataIris;
    double* normalizeDataIris;
    char*  nameIris;
}DataIris;

typedef struct{
    double* average;
    int ** result;
    DataIris** neuronne;
}DataNeuronne;

typedef struct{
    double distance_to_the_bmu;
    int     i_bmu;
    int     j_bmu;
}BestMatchUnit;

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
    //Calculate the "voisinage" contening the 50% neuronne
    int k = 1;
    while (pow(2 * k + 1, 2) -1 < (int)(size.horizontal * size.vertical / 2)) k ++;
    size.voisinage = k;
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

    dataNeuronne->result =  (int**) malloc (size.horizontal * sizeof(int));
    for(int i=0; i< size.horizontal; i++)
        dataNeuronne->result[i] = (int*) malloc (size.vertical * sizeof(int));

    dataNeuronne->neuronne =  (DataIris**) malloc (size.horizontal * sizeof(DataIris));
    for(int i=0; i< size.horizontal; i++){
        dataNeuronne->neuronne[i] = (DataIris*) malloc (size.vertical * sizeof(DataIris));
        for(int j=0; j< size.vertical; j++){
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
//Find the Best Match Unit
BestMatchUnit* Winner_Neuronne (BestMatchUnit* bmu, double* normalizeIris, DataIris** neuronne, int k){
    double distance;
    bmu->distance_to_the_bmu = DBL_MAX;
    for(int i=0; i< size.horizontal; i++){
         for(int j=0; j< size.vertical; j++){
             distance = distance_neuronne (normalizeIris, neuronne[i][j].dataIris, size.columnIris);
             //printf("Iris %d and (%d,%d) are with distance: %f\n", k, i, j, distance);
             if(distance < bmu->distance_to_the_bmu ){
                 bmu->distance_to_the_bmu = distance;
                 bmu->i_bmu = i;
                 bmu->j_bmu = j;
             } 
         }
    }
   return bmu;
} 
//Propagation to neighbor
void propagation (DataNeuronne* dataNeuronne, double* normalizeIris, BestMatchUnit* bmu, double alpha, int neighbor){
    int i_start, i_end, j_start, j_end;
    //Top
    if(bmu->i_bmu < neighbor) i_start = 0;
        else i_start = bmu->i_bmu - neighbor;
    //Bottom
    if(bmu->i_bmu >= size.horizontal - neighbor) i_end = size.horizontal - 1;
        else i_end = bmu->i_bmu + neighbor;
    //Right
    if(bmu->j_bmu < neighbor) j_start = 0;
        else j_start = bmu->j_bmu - neighbor;
    //Left
    if(bmu->j_bmu >= size.vertical - neighbor) j_end = size.vertical - 1;
        else j_end = bmu->j_bmu + neighbor;
    //printf("de i=%d - i=%d et j=%d -j=%d\n", i_start, i_end, j_start, j_end);
        //propagation to neighbor
    for(int i=i_start; i<= i_end; i++){
        for(int j=j_start; j<= j_end; j++){
            for(int k=0; k< size.columnIris; k++){
                dataNeuronne->neuronne[i][j].dataIris[k] += alpha * (normalizeIris[k] - dataNeuronne->neuronne[i][j].dataIris[k]);
            }
        }
    }
}
//Learnning
DataNeuronne* Learning_Neuronnes (DataIris *data, DataNeuronne* dataNeuronne, BestMatchUnit* bmu, int* Rand, int itteration, int neighbor, double alpha){
    srand(time(NULL));
    for(int i=0; i< itteration; i++){
        alpha = alpha - (double)i / (double)itteration;
        for(int k=0; k< size.lineIris; k++){
            bmu = Winner_Neuronne (bmu, data[Rand[k]].normalizeDataIris, dataNeuronne->neuronne, Rand[k]);
            //printf("Iris %d win (%d,%d) with distance: %f\n", Rand[k], bmu->i_bmu, bmu->j_bmu, bmu->distance_to_the_bmu);
            propagation (dataNeuronne, data[Rand[k]].normalizeDataIris, bmu, alpha, neighbor);
        }
        //printf("\n");
    }
    return dataNeuronne;
}
//Etiquettage
void Etiquettage (DataIris *data, DataNeuronne* dataNeuronne, int* Rand){
    /* for(int i=0; i< size.horizontal; i++)
        for(int j=0; j< size.vertical; j++)
                dataNeuronne->result[i][j] = 0; */

    for(int i=0; i< size.horizontal; i++){
         for(int j=0; j< size.vertical; j++){
             for(int k=0; k< size.lineIris; k++){
                int count = 0;
                for(int l=0; l< size.columnIris; l++)
                     if(dataNeuronne->neuronne[i][j].dataIris[l] == data[Rand[k]].normalizeDataIris[l]) count ++;
                if(count == size.columnIris){
                    if(strcmp(data[Rand[k]].nameIris, "Iris-setosta") == 0) dataNeuronne->result[i][j] = 1;
                    if(strcmp(data[Rand[k]].nameIris, "Iris-versicolor") == 0) dataNeuronne->result[i][j] = 2;
                    if(strcmp(data[Rand[k]].nameIris, "Iris-virginica") == 0) dataNeuronne->result[i][j] = 3;
                        else dataNeuronne->result[i][j] = 0;
                }
            }
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

void display_result_neuronne (DataNeuronne *dataNeuronne){
    printf("\nResult Neuronnes\n");
    for(int i=0; i< size.horizontal; i++){
         for(int j=0; j< size.vertical; j++)
             printf("%d ", dataNeuronne->result[i][j]);
         printf("\n");
}
}
void freeSpace (DataIris* data, DataNeuronne* dataNeuronne, BestMatchUnit* bmu){
    //free dataIris
    for(int i=0; i< size.lineIris; i++){
        free(data[i].dataIris);
        free(data[i].normalizeDataIris); 
    }
    free(data);

    //free dataNeuronne
    //for(int i=0; i< size.horizontal; i++) free(dataNeuronne->result[i]);

    for(int i=0; i< size.horizontal; i++){
        for(int j=0; j< size.vertical; j++){
            free(dataNeuronne->neuronne[i][j].dataIris);
        }
        free(dataNeuronne->neuronne[i]);
    }
    free(dataNeuronne);
    
    //free best match unit
    free(bmu);
}
#endif