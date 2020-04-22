#ifndef __IRIS__H_
#define __ISIS__H_

//Displays
void display_database (DataIris *data, int ligne, int colonne ){
    int i,j;
    printf("Espace de données:\n");
    for( i=0; i< ligne; i++){
        for( j=0; j< colonne; j++){
            printf("%f  ", data[i].dataIris[j]);
        }
        printf("%s\n", data[i].nameIris);
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
        printf("Iris %d: ",i);
        for( j=0; j< colonne; j++){
            printf("%f  ", data[i].normalized[j]);
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
    for(int i=0; i< size.vertical; i++){
         for(int j=0; j< size.horizontal; j++){
             printf("\ni=%d, j=%d:    ",i,j);
             for(int k=0; k< size.columnIris; k++){
                 printf("k=%d: %f  ", k, dataNeuronne->neuronne[i][j][k]);
             }
         }
         printf("\n");
     }         
} 

void display_result_neuronne (DataNeuronne *dataNeuronne){
    printf("\nResult Neuronnes\n");
    int value;
    for(int i=0; i< size.vertical; i++){
         for(int j=0; j< size.horizontal; j++){
             value = dataNeuronne->result[i][j];
             if (value == 1) {
				printf("\033[22;31m%d ", value);
			} else if (value == 2) {
				printf("\033[22;32m%d ", value);
			} else if (value == 3) {
				printf("\033[22;34m%d ", value);
			} else {
				printf("\033[22;37m%d ", value);
			}
         }
         printf("\n");
    }
}
void freeSpace (DataIris* data, DataNeuronne* dataNeuronne, BestMatchUnit* bmu){
    //free dataIris
    for(int i=0; i< size.lineIris; i++){
        free(data[i].dataIris);
        free(data[i].normalized); 
    }
    free(data);

    //free dataNeuronne
    //for(int i=0; i< size.horizontal; i++) free(dataNeuronne->result[i]);

    for(int i=0; i< size.vertical; i++){
        for(int j=0; j< size.horizontal; j++){
            free(dataNeuronne->neuronne[i][j]);
        }
        free(dataNeuronne->neuronne[i]);
    }
    free(dataNeuronne);
    
    //free best match unit
    free(bmu);
}

#endif