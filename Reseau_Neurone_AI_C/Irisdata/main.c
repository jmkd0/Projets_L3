#include <stdio.h>
#include <stdlib.h>
#include "irisneurone.h"

int main(){
    int i,j;

    DataIris* data = (DataIris*) malloc(nbreLine*sizeof(DataIris));
    DataNeuronne*  dataNeuronne = ( DataNeuronne* )malloc( sizeof( DataNeuronne ));

        /*  Charge data from the database */
    ChargeDatabase (data, nbreColonne);

        /*  Normalize the datas          */
    NormalizeMatrix (data, nbreLine, nbreColonne);

        /*  Calculate the average of vectors */
    dataNeuronne = MoyenneMatrix (data, nbreLine, nbreColonne);
    
        /*  Drow the neuronal space */
    EnvDonneeNeuronne (dataNeuronne , nbreNeuronne, nbreColonne);

//Displays
    display_database (data, nbreLine, nbreColonne );
    display_nameflower (data, nbreLine);
    display_normalise (data, nbreLine, nbreColonne);
    display_moyenne ( dataNeuronne, nbreColonne);
    display_neuronne_space ( dataNeuronne, nbreNeuronne, nbreColonne);
  
    return 0;
}