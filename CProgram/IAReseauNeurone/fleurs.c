#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define linesize 100
#define nbrevectors 150
#define nbrecolonne 5
typedef struct{
    double val1;
    double val2;
    double val3;
    double val4;
    char  name[nbrevectors];
}Datas;
void chargeDatabase(Datas *datas){
    FILE* fichier ;
    char ligne[100];
    char *endvalue=",";
    char *chaine;
    int compterline=0;
    fichier= fopen("iris.data", "r") ;
    if (fichier != NULL){
        while ( fgets( ligne, linesize, fichier) != NULL ){
            chaine=strtok(ligne, endvalue); datas[compterline].val1=atof(chaine);
            chaine=strtok(NULL, endvalue); datas[compterline].val2=atof(chaine);
            chaine=strtok(NULL, endvalue); datas[compterline].val3=atof(chaine);
            chaine=strtok(NULL, endvalue); datas[compterline].val4=atof(chaine); 
            chaine=strtok(NULL, endvalue); strcpy(datas[compterline].name, chaine);      
           compterline++;
    }
    fclose( fichier ) ;
    }
}
void main(){
    Datas datas[nbrevectors];
    chargeDatabase(datas);
    
    int i;
    for(i=0; i<150; i++){
        printf("%f %f %f %f %s\n",datas[i].val1,datas[i].val2,datas[i].val3,datas[i].val4,datas[i].name);
         
    }
    
}