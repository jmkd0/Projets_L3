#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define linesize 100
#define nbreline 3
#define nbreneuronne 60
#define nbrecolonne 4

typedef struct{
    double iris[nbrecolonne];
    double normalize[nbrecolonne];
    char  name[linesize];
}DatasIris;

typedef struct{
    double moyenne[nbrecolonne];
    double neuronne[nbrecolonne][nbreneuronne];
}DatasNeuronne;
void chargeDatabase(DatasIris *datas, int colonne){
    FILE* fichier ;
    char ligne[linesize];
    char *endvalue=",";
    char *chaine;
    int compterline=0, comptercolonne;
    fichier= fopen("test.data", "r") ;/*https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data*/
    if (fichier != NULL){
        while ( fgets( ligne, linesize, fichier) != NULL ){
            comptercolonne=0;
            chaine=strtok(ligne, endvalue);
            while(comptercolonne < colonne){
                datas[compterline].iris[comptercolonne]=atof(chaine);
                chaine=strtok(NULL, endvalue);
                comptercolonne++;
            }
            strcpy(datas[compterline].name, chaine);
           compterline++;
    }
    fclose( fichier ) ;
    }
}


void normalizeMatrix(DatasIris *datas, int ligne, int colonne){
    int i,j;
    double norme;
    for(j=0; j<colonne; j++){
        norme=0;
        for(i=0; i<ligne; i++)
                norme += pow(datas[i].iris[j],2);
        norme = sqrt(norme);
        for(i=0; i<ligne; i++)
            datas[i].normalize[j] = datas[i].iris[j]/norme;
    }
}
void moyenneMatrix(DatasIris *datas, DatasNeuronne dataneuronne, int ligne, int colonne){
    double mean;
    int i,j;
    for(j=0; j< colonne; j++){
        mean=0;
        for(i=0; i< ligne; i++){
            mean += datas[i].normalize[j];
            
        }
        mean /= ligne;
        dataneuronne.moyenne[j] = mean;
        printf("%f", dataneuronne.moyenne[j]);
    }

}

int main(){
    DatasIris datas[nbreline];
    DatasNeuronne dataneuronne;
    chargeDatabase(datas, nbrecolonne);
    normalizeMatrix(datas, nbreline, nbrecolonne);
    moyenneMatrix(datas, dataneuronne, nbreline, nbrecolonne);

    int i,j;
    /*for(i=0; i<nbreline; i++){
        for(j=0; j<nbrecolonne; j++){
            printf("%f  ",datas[i].normalize[j]);
        }
        printf("\n");
    }*/
    for(i=0; i<nbrecolonne; i++){
        printf("%f ",dataneuronne.moyenne[i]);
    }
    
    return 0;
}