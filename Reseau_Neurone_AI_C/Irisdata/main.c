#include <stdio.h>
#include <stdlib.h>
#include "irisneurone.h"
typedef struct S{
    int** M;
}S;
int main(){
    int j;
    char* fileName = "iris.data"; /*https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data*/

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

        /*  Parcours aléatoire */
    int *Rand = Rand_Table ( size.lineIris );

        /*  Déterminer les neuronnes gagnants */
    BestMatchUnit* bmu = (BestMatchUnit*) malloc (sizeof(BestMatchUnit));
    dataNeuronne = Learning_Neuronnes (data, dataNeuronne, bmu, Rand, size.ordonnencement, size.voisinage, size.alpha_ordonn);
    dataNeuronne = Learning_Neuronnes (data, dataNeuronne, bmu, Rand, size.affinage, 1 , size.alpha_affin);

        /* Etquettage */
    Etiquettage (data, dataNeuronne, Rand);
    //Displays
    //display_database (data, size.lineIris, size.columnIris );
    //display_nameflower (data, size.lineIris);
    //display_normalise (data, size.lineIris, size.columnIris);
    //display_average ( dataNeuronne, size.columnIris);
    //display_neuronne_space ( dataNeuronne);
    display_result_neuronne ( dataNeuronne );
    
    //Free space
    freeSpace (data, dataNeuronne, bmu);




    return 0;
}