#include "iris.h"

int main() {
	irisData_t *iris_tab;
	irisRand_t *iris_shuffled;
	irisData_t *iris_average;
	int number_line;

	irisData_t *iris_interval_upper;
	irisData_t *iris_interval_lower;
	double interval = 0.1f;

	net_t *net;
	irisData_t *nodes;

	int number_node_horiz = 10;
	int number_node_verti = 6;

	FILE* file_opened = fopen("../Irisdata/iris.data", "r");
	if (!file_opened) {
		printf("Can't open this file !\n");
		exit(1);
	}

	number_line = count_number_line(file_opened);

	iris_tab = allocIrisData_t(number_line);

	take_line(file_opened, iris_tab);

	//print_data(iris_tab, number_line);

	//printf("\n/////////////////////////////////////////////\n\nNorm of the vector:\n\n");

	normalize(iris_tab, number_line);

	//print_data(iris_tab, number_line);

	//printf("\n/////////////////////////////////////////////\n\nShuffle the vector:\n\n");

	iris_shuffled = malloc(number_line * sizeof(irisRand_t));

	srand(time(NULL));
	 int *Rand = Rand_Table ( 150 );
	shuffle_data(iris_tab, iris_shuffled, number_line);

	//print_shuffle_data(iris_shuffled, number_line);

	iris_average = average(iris_tab, number_line);

	printf("\nVecteur moyen\n");
	print_data(iris_average, 1);

	//iris_interval_upper = interval_bound(iris_average, 1, interval);
	//iris_interval_lower = interval_bound(iris_average, 0, interval);

	/*printf("\nLimite inférieure\n");
	print_data(iris_interval_lower, 1);
	printf("\nLimite supérieure\n");
	print_data(iris_interval_upper, 1);*/

	//printf("\nVecteur de neurones\n");
	net = random_in_interval(iris_average, iris_interval_lower, iris_interval_upper, number_node_horiz, number_node_verti);
	net->neighborhood = 3; // la variable net est alloué dans la fonction rand_in_interval, donc on peut met cette assignation ici

	print_net_map_node(net, number_node_horiz, number_node_verti);

	printf("\n\033[22;31mIris-setosa\n");
	printf("\033[22;32mIris-versicolor\n");
	printf("\033[22;34mIris-virginica\033[22;37m\n");

	int** resultat;
	resultat = malloc(number_node_verti * sizeof(int*));
	for (int i = 0; i < number_node_verti; i++) {
		resultat[i] = malloc(number_node_horiz * sizeof(int));
	}
	
	printf("\nOrdonnancement\n");
	int iteration_max = 500;
	apprentissage (3, 1, Rand, iteration_max, iris_shuffled, net, number_line, number_node_horiz, number_node_verti);
	//etiquettage (net, iris_shuffled, number_line, number_node_horiz, number_node_verti, resultat);

	printf("\nAffinage\n");
	iteration_max = 1500;
	//apprentissage (3, 1, Rand, iteration_max, iris_shuffled, net, number_line, number_node_horiz, number_node_verti);
	etiquettage (net, Rand, iris_shuffled, number_line, number_node_horiz, number_node_verti, resultat);

print_shuffle_data(iris_shuffled, number_line);
print_net_map_node(net, number_node_horiz, number_node_verti);

	fclose(file_opened);
	free(iris_tab);
	free(iris_shuffled);
	free(resultat);
	free(net);
	return 0;
}