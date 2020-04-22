#ifndef __IRIS__H_
#define __ISIS__H_

typedef struct List{
    BestMatchUnit* value;
    struct List *next;
} List;

/* Liste chainnée */
void addBack (List* list, BestMatchUnit* value){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    List* end = list;
    while(end->next != NULL) end =end->next;
    node->value = value;
    node->next = NULL;
    end->next = node;
}
void eraseBack (List* list){
    List* last = list;
    if(list->next == NULL) exit( EXIT_FAILURE);
    while(last->next->next != NULL) last = last->next;
    free(last->next->next);
    last->next = NULL;
}
/* Mise en place de tableau de valeurs aléatoires */

int* Rand_Table ( int b ){
    int *Rand = (int*) malloc(b*sizeof(int));
    int i, random, t, a=0;
    for( i=0; i<b; i++) Rand[i] = i;
    for( i= 0; i<b; i++){
        random = rand()%(b-a)+a;
        t= Rand[i];
        Rand[i]=Rand[random];
        Rand[random]=t;
    }
    return Rand;
} 

//Function to calculate the distance between two vector or datas
double distance_neuronne ( double *Tab1, double *Tab2, int ligne){
    int i;
    double distance = 0;
    for (i=0; i < ligne; i++)
        distance += pow (Tab1[i]-Tab2[i], 2);
    distance = sqrt (distance);
    return distance;
}
//Find the Best Match Unit
BestMatchUnit* Winner_Neuronne (BestMatchUnit* bmu, double* normalizeIris, double*** neuronne, int k){
    double distance = 0;
    List  *list = &(List){0, NULL};
    bmu->distance_to_the_bmu = DBL_MAX;
    for(int i=0; i< size.vertical; i++){
         for(int j=0; j< size.horizontal; j++){
             distance = distance_neuronne (normalizeIris, neuronne[i][j], size.columnIris);
             //printf("Iris %d and (%d,%d) are with distance: %f\n", k, i, j, distance);
             if(distance < bmu->distance_to_the_bmu ){
                 while(list->next != NULL) eraseBack (list); 
                 bmu->distance_to_the_bmu = distance;
                 bmu->i_bmu = i;
                 bmu->j_bmu = j;
                 addBack(list, bmu);
             }/* else if(distance == bmu->distance_to_the_bmu ){
                 bmu->distance_to_the_bmu = distance;
                 bmu->i_bmu = i;
                 bmu->j_bmu = j;
                 addBack(list, bmu);
             } */
         }
    }
   //Choix aleatoire parmi les bests match unit
            /* int cpt = 0;
            List  *N = list;
            while(N->next != NULL) {
                cpt++;
                N = N->next;
            }
            srand(time(NULL));
            cpt = rand()%cpt+1;
            int pos=0;
            while(pos != cpt && list->next != NULL){ list = list->next; pos++;}
            //printf("Le neuronne plus proche est: (%d,%d) avec distance %f parmis %d",list->value->i_bmu, list->value->j_bmu,list->value->distance_to_the_bmu, pos);
   return list->value; */
   return bmu;
} 

//Propagation to neighbor
double*** Propagation_Childs (double*** neuronne, double* normalized, BestMatchUnit* bmu, double alpha, int neighbor, int* Rand){
    int i_start, i_end, j_start, j_end;
    //Left
    if(bmu->i_bmu < neighbor) j_start = 0;
        else j_start = bmu->i_bmu - neighbor;
    //Top
    if(bmu->j_bmu < neighbor) i_start = 0;
        else i_start = bmu->j_bmu - neighbor;
    //Right
    if(bmu->i_bmu >= size.horizontal - neighbor) j_end = size.horizontal - 1;
        else j_end = bmu->i_bmu + neighbor;
    //Bottom
    if(bmu->j_bmu >= size.vertical - neighbor) i_end = size.vertical - 1;
        else i_end = bmu->j_bmu + neighbor;
    /* //Top
    if(bmu->i_bmu < neighbor) i_start = 0;
        else i_start = bmu->i_bmu - neighbor;
    //Bottom
    if(bmu->i_bmu >= size.vertical - neighbor) i_end = size.vertical - 1;
        else i_end = bmu->i_bmu + neighbor;
    //Right
    if(bmu->j_bmu < neighbor) j_start = 0;
        else j_start = bmu->j_bmu - neighbor;
    //Left
    if(bmu->j_bmu >= size.horizontal - neighbor) j_end = size.horizontal - 1;
        else j_end = bmu->j_bmu + neighbor; */
    
        //propagation to neighbor
    for(int i=i_start; i<= i_end; i++){
        for(int j=j_start; j<= j_end; j++){
            for(int k=0; k< size.columnIris; k++){
                neuronne[i][j][k] = neuronne[i][j][k] + alpha * (normalized[k] - neuronne[i][j][k]);
             }
        }
    }
    return neuronne;
}
//Learnning
double*** Learning_Neuronnes (DataIris *data, double*** neuronne, BestMatchUnit* bmu, int* Rand, int itteration, int neighbor, double alpha){
    srand(time(NULL));
    double alpha_max = alpha;
    for(int i=0; i< 3/* itteration */; i++){
        //int *Rand = Rand_Table ( size.lineIris );
            alpha = alpha_max * (1 - ((double)i / (double)itteration));
        for(int k=0; k< size.lineIris; k++){
            bmu = Winner_Neuronne (bmu, data[Rand[k]].normalized, neuronne, Rand[k]);
            printf("Rand %d win (%d,%d)\n",Rand[k],bmu->i_bmu, bmu->j_bmu);
            neuronne = Propagation_Childs (neuronne, data[Rand[k]].normalized, bmu, alpha, neighbor, Rand);
        }
        
        //printf("\n");
    }
    return neuronne;
}
//Etiquettage
void Etiquettage (DataIris *data, DataNeuronne* dataNeuronne, int* Rand){
    double d1, d2;
    
        for(int i=0; i< size.vertical; i++){
             for(int j=0; j< size.horizontal; j++){
                 for(int k=0; k< size.lineIris; k++){
                    int count = 0;
                    for(int l=0; l< size.columnIris; l++){
                        if( dataNeuronne->neuronne[i][j][l] == data[Rand[k]].normalized[l] ) count ++;
                     }      
                     if(count != 0) printf("count %d", count);
                    if(count == size.columnIris){
                        if(strcmp(data[Rand[k]].nameIris, categories[0]) == 0) dataNeuronne->result[i][j] = 1;
                        if(strcmp(data[Rand[k]].nameIris, categories[1]) == 0) dataNeuronne->result[i][j] = 2;
                        if(strcmp(data[Rand[k]].nameIris, categories[2]) == 0) dataNeuronne->result[i][j] = 3;
                    }
            }
        }
    }
}

#endif