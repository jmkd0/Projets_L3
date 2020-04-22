#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define NUMBER_DATA 4

typedef struct iris {
	double* value;
	double size_line;
	char* name;
	int index;
} irisData_t;

// La structure irisRand_t est utilisée pour obtenir un tableau d'adresse d'irisData_t
typedef struct irisRand {
	int index;
	irisData_t* irisDataTab;
} irisRand_t;

typedef struct net {
	double *capteur;
	double alpha;
	irisData_t **map;
	int neighborhood; // Rayon de voisinage
} net_t;

typedef struct dist_eucli {
	double distance;
	int x;
	int y;
} dist_eucli_t;


irisData_t* allocIrisData_t(int size) {
	irisData_t* tmp;
	int i;
	tmp = malloc(size * sizeof(irisData_t));
	for(i = 0; i < size; i++) {
		tmp[i].value = malloc(NUMBER_DATA * sizeof(double));
		tmp[i].name = malloc(256 * sizeof(char));
	}
	return tmp;
}

int count_number_line(FILE* file_opened) {
	int current_line = 0;
	int i = 0;
	while (1) {
		current_line = fgetc(file_opened);
		if (current_line == '\n') {
			i++;
		}
		if (current_line == EOF) {
			i++;
			break;
		}
	}
	return i;
}

void print_data(irisData_t* iris_tab, int number_line) {
	int i, j = 0;
	for(i = 0; i < number_line; i++) { // General print loop
		printf("%d : ", iris_tab[i].index);
		for (j = 0; j < NUMBER_DATA; j++) { // print value
			printf("%f ", iris_tab[i].value[j]);
		}
		printf(" %s\n", iris_tab[i].name); // print name
	}
}

void print_shuffle_data(irisRand_t *iris_shuffled, int number_line) {
	int i, j;
	for (i = 0; i < number_line; i++) {
		printf("%d : ", iris_shuffled[i].index);
		for (j = 0; j < NUMBER_DATA; j++) { // print value
			printf("%f ", iris_shuffled[i].irisDataTab->value[j]);
		}
		printf(" %s\n", iris_shuffled[i].irisDataTab->name); // print name
	}
}

void take_line(FILE* file_opened, irisData_t* iris_tab) {
	int size_current_line = 100;
	char * current_line = malloc(size_current_line * sizeof(char));
	fseek(file_opened, 0, SEEK_SET); // Return to the first character of the file

	int i = 0, j = 0;

	while (fgets(current_line, size_current_line, file_opened) != NULL) {
		iris_tab[i].size_line = strlen(current_line);
		iris_tab[i].index = i;

		if (iris_tab[i].size_line > 1) {
			j = 0; // Reset j
			iris_tab[i].value[j] = atof(strtok(current_line, ","));
			for(j = 1; j < NUMBER_DATA; j++) {
				iris_tab[i].value[j] = atof(strtok(NULL, ","));
			}
			iris_tab[i].name = strdup(strtok(NULL, "\n"));
		}
		i++;
	}
}

void normalize(irisData_t *iris_norm, int number_line) {
	double norm_vector = 0;
	int i, j;

	for (i = 0; i < NUMBER_DATA; i++) {
		norm_vector += pow(iris_norm[0].value[i], 2);
	}

	norm_vector = sqrt(norm_vector); // Ici, j'ai la norme du vecteur

	for (i = 0; i < number_line; i++) {
		for (j = 0; j < NUMBER_DATA; j++) {
			iris_norm[i].value[j] = iris_norm[i].value[j] / norm_vector; 
		}
	}
}

void shuffle_data(irisData_t *iris_tab, irisRand_t *iris_shuffled, int number_line) {
	irisRand_t tmp;
	int i, j;
	int num; // Random number

	// Initialize the vector iris_shuffled
	for (int i = 0; i < number_line; i++) {
		iris_shuffled[i].index = i;
		iris_shuffled[i].irisDataTab = &iris_tab[i]; // Get the adress of the pointer
	}

	// Shuffle the data of the vector
	/* for (i = 0; i < number_line; i++) {
		num = (rand() % (number_line - i)) + i; // On choisit un nombre aléatoire en excluant les index déjà remplacés
		for(j = 0; j <= num; j++) {
			if (j == num) {
				tmp = iris_shuffled[i];
				iris_shuffled[i] = iris_shuffled[j];
				iris_shuffled[j] = tmp;
			}
		}
	} */
}

irisData_t* average (irisData_t *iris_tab, int number_line) {
	irisData_t *iris_average = allocIrisData_t(1);
	int i, j;
	for (i = 0; i < NUMBER_DATA; i++) {
		for (j = 0; j < number_line; j++) {
			iris_average->value[i] += iris_tab[j].value[i];
		}
		iris_average->value[i] /= number_line;
        printf("%f ",iris_average->value[i]);
	}
    
	return iris_average;
}

irisData_t* interval_bound (irisData_t *iris_tab, int boolean, double interval) {
	int i;
	irisData_t* iris_interval = allocIrisData_t(1);
	for (i = 0; i < NUMBER_DATA; i++) {
		iris_interval->value[i] = iris_tab->value[i];
		if (boolean == 1) {
			iris_interval->value[i] += interval;
		} else {
			iris_interval->value[i] -= interval;
		}
	}
	return iris_interval;
}

net_t* allocNet_t (int size_horiz, int size_verti) {
	net_t* tmp;
	int i;
	tmp = malloc(sizeof(net_t));
	tmp->capteur = malloc(NUMBER_DATA * sizeof(double));
	tmp->map = malloc(size_verti * sizeof(irisData_t*));
	for (i = 0; i < size_verti; i++) {
		tmp->map[i] = malloc(size_horiz * sizeof(irisData_t));
	}
	return tmp;
}

void print_net_map_node(net_t *net, int number_node_horiz, int number_node_verti) {
	int i, j , k;
	for (i = 0; i < number_node_verti; i++) {
		for (j = 0; j < number_node_horiz; j++) {
			printf("\ni=%d, j=%d    ", i, j);
			for(k = 0; k < NUMBER_DATA; k++) {
				printf("k=%d: %f  ", k, net->map[i][j].value[k]);
			}
		}
        printf("\n");
	}
}

net_t* random_in_interval (irisData_t *iris_tab, irisData_t *lower, irisData_t *upper, int number_node_horiz, int number_node_verti) {
	int i, j, k;
	double num; // Random number
	net_t* net = allocNet_t(number_node_horiz, number_node_verti); // Contient la variable map qui est un tab à 2 dimensions
	int number_node_total = number_node_horiz * number_node_verti;
	irisData_t *node = allocIrisData_t(number_node_total); // Tableau à 1 dimension

	/* for (i = 0; i < number_node_total; i++) {
		for (j = 0; j < NUMBER_DATA; j++) {
			num = (rand() / (double)RAND_MAX) * (upper->value[j] - lower->value[j]) + lower->value[j];
			node[i].value[j] = num;
		}
	}

	for (i = 0; i < number_node_verti; i++) {
		for (j = 0; j < number_node_horiz; j++) {
			for(k = 0; k < NUMBER_DATA; k++) {
				net->map[i][j] = node[i * number_node_horiz + j];
			}
		}
	} */
    for (i = 0; i < number_node_verti; i++) {
		for (j = 0; j < number_node_horiz; j++) {
			for(k = 0; k < NUMBER_DATA; k++) {
				net->map[i][j].value = (double*) malloc (NUMBER_DATA * sizeof(double));
			}
		}
	} 
    
    double minimum, maximum;
    for(k = 0; k < NUMBER_DATA; k++) {
        minimum = iris_tab->value[k] - 0.1;
        maximum = iris_tab->value[k] + 0.1;
	    for (i = 0; i < number_node_verti; i++) {
	    	for (j = 0; j < number_node_horiz; j++) {
            
	    		net->map[i][j].value[k] = (rand()/(double)RAND_MAX)*(maximum-minimum)+minimum;
	    	}
	    }
	} 
	return net;
}

dist_eucli_t** allocdist_eucli_t (int size_horiz, int size_verti) {
	dist_eucli_t **tmp;
	int i;
	tmp = malloc(size_verti * sizeof(dist_eucli_t*));
	for (i = 0; i < size_verti; i++) {
		tmp[i] = malloc(size_horiz * sizeof(dist_eucli_t));
	}
	return tmp;
}

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

dist_eucli_t** find_bmu (net_t *net, double* capteur, int number_node_horiz, int number_node_verti) {
	int i, j, k;
	double distance;

	dist_eucli_t **distance_tab; // Tableau de distance euclidienne
	distance_tab = allocdist_eucli_t(number_node_horiz, number_node_verti);

	dist_eucli_t **bmu; // Variable qui contiendra le BMU
	bmu = allocdist_eucli_t(1, 1);

	/**
	 * Calcule la distance euclidienne entre un vecteur de donnée (net->capteur) 
	 * et chacun des vecteurs de neurone de la map
	 */
	for (i = 0; i < number_node_verti; i++) { 
		for (j = 0; j < number_node_horiz; j++) {
			distance = 0.0;
			for (k = 0; k < NUMBER_DATA; k++) {
				distance = distance + pow(fabs(net->map[i][j].value[k] - capteur[k]), 2);
			}
			distance = sqrt(distance);
			//printf("i : %d, j: %d, Distance euclidienne : %f\n", i, j, distance);
			distance_tab[i][j].distance = distance;
			distance_tab[i][j].x = j;
			distance_tab[i][j].y = i;
		}
	}

	// Recherche du BMU dans le tableau de distance euclidienne
    bmu[0][0].distance = 100;
    double dist=0;
	for (i = 0; i < number_node_verti; i++) {
		for (j = 0; j < number_node_horiz; j++) {
			if (distance_tab[i][j].distance < bmu[0][0].distance) {  // Si la valeur est plus petite que la distance sélectionnée
				bmu[0][0].distance = distance_tab[i][j].distance;
				bmu[0][0].x = i;
				bmu[0][0].y = j;
			}
            /* dist = distance_tab[i][j].distance;
            if(dist < bmu[0][0].distance){
                bmu[0][0].distance = dist;
				bmu[0][0].x = i;
				bmu[0][0].y = j;
            } */
		}
	}
    //printf("bmu:(%d,%d)   \n",bmu[0][0].y, bmu[0][0].x);
	return bmu;
}

void voisin (net_t *net, double* capteur, dist_eucli_t **bmu, int neigh,  int number_node_horiz, int number_node_verti, int alpha) {
	int i, j, k;
	int i_start, j_start, i_end, j_end;
	net_t *net_next = allocNet_t(number_node_horiz, number_node_verti);

	// Limite gauche
	if (bmu[0][0].x < neigh) { 
		j_start = 0;
	} else {
		j_start = bmu[0][0].x - neigh;
	}

	 // Limite haute
	if (bmu[0][0].y < neigh) {
		i_start = 0;
	} else {
		i_start = bmu[0][0].y - net->neighborhood;
	}	

	// Limite droite
	if (bmu[0][0].x > number_node_horiz - neigh) { 
		j_end = number_node_horiz;
	} else {
		j_end = bmu[0][0].x + neigh;
	}

	// Limite basse
	if (bmu[0][0].y > number_node_verti - neigh) { 
		i_end = number_node_verti;
	} else {
		i_end = bmu[0][0].y + neigh;
	}

	for (i = i_start; i < i_end; i++) {
		for (j = j_start; j < j_end; j++) {
			for (k = 0; k < NUMBER_DATA; k++) {
				net->map[i][j].value[k] = net->map[i][j].value[k] + alpha * (capteur[k] - net->map[i][j].value[k]);
			
            }
            //if(i==0 && j== 0) printf("neur %f     iri %f   \n",net->map[i_end-1][j_end-1].value[0], net->capteur[0]);
		}
	}
    //printf("bmu:(%d,%d) i:(%d,%d) j:(%d,%d)neur %f     iri %f   \n",bmu[0][0].y, bmu[0][0].x, i_start,i_end,j_start,j_end, net->map[0][0].value[0], net->capteur[0]);
}

void etiquettage (net_t *net,int* Rand, irisRand_t *iris_shuffled, int number_line, int number_node_horiz, int number_node_verti, int** resultat) {
	int i, j, k, l;
	int identique = 0;
	int res[number_node_verti][number_node_horiz];

	for (i = 0; i < number_node_verti; i++) {
		for (j = 0; j < number_node_horiz; j++) {
			resultat[i][j] = 0;
		}		
	}

	for (i = 0; i < number_node_verti; i++) { // Pour chaque vecteur de neurone
		for (j = 0; j < number_node_horiz; j++) {
			//printf("i = %d, j  = %d\n", i, j);
			for (k = 0; k < number_line; k++) { // On compare à chaque vecteur de donnée
				identique = 0;
				for (l = 0; l < NUMBER_DATA; l++) {       // Les valeurs de chaque donnée
					if (net->map[i][j].value[l] == iris_shuffled[Rand[k]].irisDataTab->value[l]) {
						identique++;
					}
				}
				if (identique == NUMBER_DATA) {
                    //printf("%d ",identique);
					if (strcmp(iris_shuffled[Rand[k]].irisDataTab->name, "Iris-setosa") == 0) {
						resultat[i][j] = 1;	
					} else if (strcmp(iris_shuffled[Rand[k]].irisDataTab->name, "Iris-versicolor") == 0) {
						resultat[i][j] = 2;
					} else if (strcmp(iris_shuffled[Rand[k]].irisDataTab->name, "Iris-virginica") == 0) {
						resultat[i][j] = 3;
					} else {
						resultat[i][j] = 0;
					}					
				}
			}
		}
	}

	for (i = 0; i < number_node_verti; i++) {
		for (j = 0; j < number_node_horiz; j++) {
			if (resultat[i][j] == 1) {
				printf("\033[22;31m%d ", resultat[i][j]);
			} else if (resultat[i][j] == 2) {
				printf("\033[22;32m%d ", resultat[i][j]);
			} else if (resultat[i][j] == 3) {
				printf("\033[22;34m%d ", resultat[i][j]);
			} else {
				printf("\033[22;37m%d ", resultat[i][j]);
			}
		}
		printf("\033[22;37m\n");
	}
}

void apprentissage (int neigh,double alpha, int* Rand, int iteration_max, irisRand_t *iris_shuffled, net_t *net, int number_line, int number_node_horiz, int number_node_verti) {
	int i, j, k;
	int neighborhood_max = neigh;
	double alpha_max = alpha;
	dist_eucli_t **bmu;
	for (i = 0; i < iteration_max; i++) {
		alpha = alpha_max * (1- ((double)i / (double)iteration_max));

		//if ((iteration_max/neighborhood_max) - 1 == (i % (iteration_max/neighborhood_max))) {
		//	printf("rv = %d\n", net->neighborhood);
		//	//printf("%d\n", (iteration_max/neighborhood_max));
		//	net->neighborhood--;
		//}

		// Itére sur les vecteurs de données mélangés
		for (j = 0; j < number_line; j++) {
			//for (k = 0; k < NUMBER_DATA; k++) {
			//	net->capteur[k] = iris_shuffled[Rand[j]].irisDataTab->value[k];
			//}
			bmu = find_bmu (net, iris_shuffled[Rand[j]].irisDataTab->value, number_node_horiz, number_node_verti);
			voisin(net, iris_shuffled[Rand[j]].irisDataTab->value,  bmu, neigh, number_node_horiz, number_node_verti, alpha);
			//printf("dist eucli = %f, x = %d, y = %d\n", bmu[0][0].distance, bmu[0][0].x, bmu[0][0].y);	
            //if(j==0) printf("neur %f     iri %f   \n",net->map[0][0].value[0], iris_shuffled[0].irisDataTab->value[0]);
		}
	}
	//net->neighborhood = neighborhood_max;
}
// Prototype main.c
int main();