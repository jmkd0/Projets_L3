#include <stdio.h>
#include <stdlib.h>
#include "irisneurone.h"

int main(){
    int i,j;

    DataIris* data = (DataIris*) malloc(nbreIris*sizeof(DataIris));
    DataNeuronne*  dataNeuronne = ( DataNeuronne* )malloc( sizeof( DataNeuronne ));

        /*  Charge data from the database */
    ChargeDatabase (data, nbreColonne);

        /*  Normalize the datas          */
    NormalizeMatrix (data, nbreIris, nbreColonne);

        /*  Calculate the average of vectors */
    dataNeuronne = MoyenneMatrix (data, nbreIris, nbreColonne);
    
        /*  Drow the neuronal space */
    EnvDonneeNeuronne (dataNeuronne , nbreNeuronne, nbreColonne);

        /*  Déterminer les neuronnes gagnants */
    Winners_Neuronnes (data, dataNeuronne , nbreIris, nbreNeuronne, nbreColonne );

//Displays
    //display_database (data, nbreIris, nbreColonne );
    //display_nameflower (data, nbreIris);
    //display_normalise (data, nbreIris, nbreColonne);
    //display_moyenne ( dataNeuronne, nbreColonne);
    display_neuronne_space ( dataNeuronne, nbreNeuronne, nbreColonne);
  
    return 0;
}