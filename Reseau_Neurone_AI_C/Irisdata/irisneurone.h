#ifndef __IRIS__H_
#define __ISIS__H_

#include <stdio.h>
#include <stdlib.h>

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
    double neuronne[nbreNeuronne][nbreColonne];
}DataNeuronne;

void ChargeDatabase(DataIris *data, int colonne);
void NormalizeMatrix(DataIris *data, int ligne, int colonne);
DataNeuronne* MoyenneMatrix(DataIris *data, int ligne, int colonne);
void EnvDonneeNeuronne (DataNeuronne* dataNeuronne, int ligne, int colonne);

//Displays
void display_database (DataIris *data, int ligne, int colonne );
void display_nameflower (DataIris *data, int ligne);
void display_normalise (DataIris *data, int ligne, int colonne);
void display_moyenne ( DataNeuronne* dataNeuronne, int colonne);
void display_neuronne_space (DataNeuronne* dataNeuronne, int ligne, int colonne);

#endif