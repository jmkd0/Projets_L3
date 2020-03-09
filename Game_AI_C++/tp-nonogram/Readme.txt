Le fichier mynng.h contient les fonctions de gestion d'un plateau du jeu Nonogram.
Le fichier s1.cpp contient un exemple de solver MC.
* le programme joue des playouts
* quand un playout finit dans un état solution, le programme affiche la solution et s'arrête

La notion de score binaire rend le jeu difficile :
* soit la solution est trouvée et le score est 100
* soit la solution n'est pas trouvée et le score est 0
(ainsi rien n'indique la proximité à la solution)

En testant les résultats selon la suite aléatoire utilisée (de 1 à 9), le probleme 3x3 est résolu :
* en 477 itérations avec srand(4)
* en 2 itérations avec srand(8)
