#include <stdio.h>
#include <stdlib.h>
#include "irisneurone.h"

int main(){
    int j;
    char* fileName = "test.data"; /*https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data*/

        /* Find size line and colum of dataIris */
    SetSizeDataIris ( fileName );

        /* set space for DataIris */
    DataIris* data = reserveSpaceDataIris (data);

        /* Charge datas from database */
    data = ChargeDatabase (fileName, data);

        /*  Normalize the datas          */
    data = NormalizeMatrix (data, size.lineIris, size.columnIris);

        /* Set space for DataNeuronne */
    DataNeuronne*  dataNeuronne = reserveSpaceDataNeuronne (dataNeuronne);

        /*  Calculate the average of vectors */
    dataNeuronne = AverageMatrix (dataNeuronne, data, size.lineIris, size.columnIris);
    
        /*  Drow the neuronal space */
    dataNeuronne = EnvDonneeNeuronne (dataNeuronne);

    //    /*  Déterminer les neuronnes gagnants */
    data = Winners_Neuronnes (data, dataNeuronne);

    //Displays
    display_database (data, size.lineIris, size.columnIris );
    display_nameflower (data, size.lineIris);
    display_normalise (data, size.lineIris, size.columnIris);
    display_average ( dataNeuronne, size.columnIris);
    display_neuronne_space ( dataNeuronne);
    display_winner_neuronne ( data );
    
    //Free space
    freeSpace (data, dataNeuronne);
    return 0;
}