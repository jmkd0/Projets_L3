#ifndef __IRIS__H_
#define __ISIS__H_

//Displays
/* Donnée de la database */
void display_database (DataIris *data ){
    int i,j;
    printf("Espace de données:\n");
    for( i=0; i< size.lineIris; i++){
        for( j=0; j< size.columnIris; j++){
            printf("%f  ", data[i].dataIris[j]);
        }
        printf("%s\n", data[i].nameIris);
    }
}

/* Noms des fleurs */
void display_nameflower (DataIris *data ){
    int i;
     printf("\nNoms des fleurs:\n");
    for( i=0; i< size.lineIris; i++){
            printf("%s \n", data[i].nameIris);
    }
    printf("\n");
}

/* Données normalisés */
void display_normalise (DataIris *data ){
    int i,j;
    printf("\nDonnées Normalisées:\n");
    for( i=0; i< size.lineIris; i++){
        printf("Iris %d: ",i);
        for( j=0; j< size.columnIris; j++){
            printf("%f  ", data[i].normalized[j]);
        }
        printf("\n");
    }
}

/* Moyenne des données */
 void display_average ( double* average){
    int i;
    printf("\nMoyenne des données:\n");
    for( i=0; i< size.columnIris; i++){
            printf("%f  ", average[i]);
    }
    printf("\n");
}

/* Espace de neuronne */
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

/* Sortie des neuronnes */
void display_result_neuronne (DataNeuronne *dataNeuronne){
    printf("\nResult Neuronnes\n");
    printf("\n\033[22;31mIris-setosa\n");
	printf("\033[22;32mIris-versicolor\n");
	printf("\033[22;34mIris-virginica\033[22;37m\n");
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

/* Libération de l'espace */
void freeSpace (DataIris* data, DataNeuronne* dataNeuronne, double* average, BMU* bmu){
    for(int i=0; i< size.lineIris; i++){
        free(data[i].dataIris);
        free(data[i].normalized); 
    }
    free(data);

    for(int i=0; i< size.vertical; i++){
        for(int j=0; j< size.horizontal; j++){
            free(dataNeuronne->neuronne[i][j]);
        }
        free(dataNeuronne->neuronne[i]);
    }
    free(dataNeuronne);
    
    //free best match unit
    free(bmu);
    free(average);
}

#endif