#ifndef __IRIS__H_
#define __ISIS__H_
#include <time.h>

/* Structure de Liste chainnée */
typedef struct List{
    BMU* value;
    struct List *next;
} List;

/* Ajout en fin de list */
void addBack (List* list, BMU* value){
    List *node= (List*)malloc(sizeof(List));
    if(node == NULL) return;
    List* end = list;
    while(end->next != NULL) end =end->next;
    node->value = value;
    node->next = NULL;
    end->next = node;
}
/* Suppression en fin de List */
void eraseBack (List* list){
    List* last = list;
    if(list->next == NULL) exit( EXIT_FAILURE);
    while(last->next->next != NULL) last = last->next;
    free(last->next->next);
    last->next = NULL;
}

/* Fonction pour générer 150 valeurs aléatoires parmi [0,149]*/
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

//Fonction pour calculer la distance entre deux vecteurs
double distance_neuronne ( double *Tab1, double *Tab2){
    int i;
    double distance = 0;
    for (i=0; i < size.columnIris; i++)
        distance += pow (Tab1[i]-Tab2[i], 2);
    distance = sqrt (distance);
    return distance;
}

//Find the Best Match Unit
BMU* Winner_Neuronne (BMU* bmu, double* normalizeIris, double*** neuronne){
    double distance = 0;
    List  *list = &(List){0, NULL};
    bmu->distance = DBL_MAX;
    for(int i=0; i< size.vertical; i++){
         for(int j=0; j< size.horizontal; j++){
             distance = distance_neuronne (normalizeIris, neuronne[i][j]);
             if(distance < bmu->distance ){
                 while(list->next != NULL) eraseBack (list);            /* on vide la liste dès qu'ont trouve */
                 bmu->distance = distance;                             /* un autre neuronne plus proche      */
                 bmu->i = i;
                 bmu->j = j;
                 addBack(list, bmu);
             }else if(distance == bmu->distance ){
                 bmu->distance = distance;
                 bmu->i = i;
                 bmu->j = j;
                 addBack(list, bmu);
             }
         }
    }
   //Choix aleatoire parmi les neuronnes les plus proche s'il y en a plusieurs
        int cpt = 0;
        List  *N = list;
        while(N->next != NULL) {
            cpt++;
            N = N->next;
        }
        srand(time(NULL));
        cpt = rand()%cpt+1;
        int pos=0;
        while(pos != cpt && list->next != NULL){ list = list->next; pos++;}
   return list->value;
} 

//Propagation to neighbors
void Propagation_Neighbors (double*** neuronne, double* normalized, BMU* bmu, int alpha, int rayon){
    //Find neighbors' raduis
    int i_start, i_end, j_start, j_end;
    //Top
    if(bmu->i < rayon) i_start = 0;
        else i_start = bmu->i - rayon;
    //Bottom
    if(bmu->i > size.vertical - rayon-1) i_end = size.vertical;
        else i_end = bmu->i + rayon;
    //Left
    if(bmu->j < rayon) j_start = 0;
        else j_start = bmu->j - rayon;
    //Right
    if(bmu->j >= size.horizontal - rayon-1) j_end = size.horizontal;
        else j_end = bmu->j + rayon; 
   
         //propagation to neighbor
    for(int i=i_start; i< i_end; i++){
        for(int j=j_start; j< j_end; j++){
            for(int k=0; k< size.columnIris; k++){
                neuronne[i][j][k] = neuronne[i][j][k] + alpha * (normalized[k] - neuronne[i][j][k]);
             }
        }
    }
}

//Function pour apprentissage Learnning

double*** Learning_Neuronnes (DataIris *data, double*** neuronne, BMU* bmu, int itteration, int rayon, double alpha){
    double alpha_max = alpha;
    int rayon_max = rayon;
    for(int i=0; i< itteration; i++){
        srand(time(NULL));
        int *Rand = Rand_Table ( size.lineIris );                       /* random              */
        alpha = alpha_max * (1 - (double)i / (double)itteration);      /* alpha               */
        rayon = rayon_max - i* rayon_max /itteration ;                /* rayon de voisinage  */
        for(int k=0; k< size.lineIris; k++){
            bmu = Winner_Neuronne (bmu, data[Rand[k]].normalized, neuronne);                    /* recherche du best match unit */
            Propagation_Neighbors (neuronne, data[Rand[k]].normalized, bmu, alpha, rayon);     /* propagation aux voisins      */
        }
    }
    return neuronne;
}

//Etiquettage
void Etiquettage (DataIris *data, DataNeuronne* dataNeuronne){
    for(int i=0; i< size.vertical; i++){
        for(int j=0; j< size.horizontal; j++){
            for(int k=0; k< size.lineIris; k++){
                int count = 0;
                for(int l=0; l< size.columnIris; l++)
                    if( dataNeuronne->neuronne[i][j][l] == data[k].normalized[l] ) count ++;
                 
                if(count == size.columnIris){
                    if(strcmp(data[k].nameIris, categories[0]) == 0) dataNeuronne->result[i][j] = 1;
                    if(strcmp(data[k].nameIris, categories[1]) == 0) dataNeuronne->result[i][j] = 2;
                    if(strcmp(data[k].nameIris, categories[2]) == 0) dataNeuronne->result[i][j] = 3;
                }
            }
        }
    }
}

#endif