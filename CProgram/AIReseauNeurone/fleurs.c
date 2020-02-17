#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define lineSize 100
#define nbreLine 150
#define nbreNeuronne 60
#define nbreColonne 4

typedef struct{
    double dataIris[nbreColonne];
    double normalizeDataIris[nbreColonne];
    char  nameIris[lineSize];
}DataIris;

typedef struct{
    double moyenne[nbreColonne];
    double neuronne[nbreColonne][nbreNeuronne];
}DataNeuronne;

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
    for(j=0; j<colonne; j++){
        norme = 0;
        for(i= 0; i < ligne; i++)
                norme += pow(data[i].dataIris[j],2);
        norme = sqrt(norme);
        for(i=0; i<ligne; i++)
            data[i].normalizeDataIris[j] = data[i].dataIris[j]/norme;
    }
}
DataNeuronne* MoyenneMatrix(DataIris *data, int ligne, int colonne){
    DataNeuronne* dataNeuronne;
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
int main(){
    int i,j;
    int tabAleatoire[nbreLine];
    DataIris* data = (DataIris*) malloc(nbreLine*sizeof(DataIris));
    DataNeuronne*  dataNeuronne = ( DataNeuronne* )malloc( sizeof( DataNeuronne ));

    ChargeDatabase (data, nbreColonne);
    NormalizeMatrix (data, nbreLine, nbreColonne);
    dataNeuronne = MoyenneMatrix (data, nbreLine, nbreColonne);
    EnvDonneeNeuronne (dataNeuronne , nbreNeuronne, nbreColonne);
    for(i=0; i<nbreLine; i++){
        tabAleatoire[i] = i+1;
    }
    for(i=0; i<nbreLine; i++){
        printf("%d ", tabAleatoire[i]);
    }

    free(data);
    return 0;
}