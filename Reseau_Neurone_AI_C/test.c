#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct Size{
    int columnIris;
    int lineIris;
}size; 

typedef struct{
    double* dataIris;
    double* normalizeDataIris;
    char*  nameIris;
}DataIris;

void ChargeDatabase(char* fileName, DataIris *data){
    FILE* fichier ;
    int lineSize = 100;
    char* ligne = (char*)malloc(lineSize*sizeof(char));
    char *chaine;   
    int compterLine=0, compterColonne;
    fichier= fopen(fileName, "r") ;
    if (fichier != NULL){
        while ( fgets( ligne, lineSize, fichier) != NULL ){
            compterColonne=0;
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
} 

void SetSizeDataIris (char* fileName){
    FILE* fichier;
    int line = 0, column = 0;
    char *chaine; 
    int lineSize = 100;
    char* ligne = (char*) malloc(lineSize * sizeof(char));
    //Column size
    fichier = fopen (fileName, "r") ;
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
}
int main(){
    int j;
    char* fileName = "test.data";
    SetSizeDataIris ( fileName );
     DataIris* data = (DataIris*) malloc (size.lineIris * sizeof(DataIris));
     for(int i=0; i< size.lineIris; i++){
         data[i].dataIris = (double*) malloc (size.columnIris * sizeof(double));
         data[i].normalizeDataIris = (double*) malloc (size.columnIris * sizeof(double));
         
     }
    ChargeDatabase (fileName, data);
    for(int i=0; i<3; i++){
        printf("%f %f %f %f %s\n",data[i].dataIris[0], data[i].dataIris[1], data[i].dataIris[2], data[i].dataIris[3],data[i].nameIris);
        
    } 
    return 0;
}