package core;
 
import java.util.Random;
import java.util.ArrayList;
 
public class IAdifficile extends AlgoIA {
    /* Nombre de parties simulés aléatoirement
 * pour chaque coup possible
 */
private static int nbSimulation;
public IAdifficile(){
    nbSimulation=10000;
}
/* Méthode abstract de la classe AlgoIA
 * Méthode appelé quand c'est au tour de L'IA de choisir une colonne (de 0 à 6)
 */
public int chooseColumn(Grid grid, Color color) {
    return monteCarlo(grid, color);
}
/* Le choix de la colonne se fait par la méthode de Monte Carlo :
 * On simule un grand nombre de parties pour chaque coup possible et le meilleur coup est celui qui a généré le plus de victoires
 */
private int monteCarlo(Grid grid, Color color) {
    //Raccourci, si il y a un coup gagnant, renvoie la colonne correspondante
    if (grid.winningMove(color)!=-1) 
        return grid.winningMove(color);
     
    boolean win;
    int count=0, colmax=0, countmax=0;
    for (int col=0; col<grid.getBoard()[0].length; col++){ //Pour chaque colonne du tableau
        if (grid.columnFull(col))                          //Si la colonne est pleine on passe à la prochaine
            continue;
        else{
            for (int k=0; k<nbSimulation; k++){             //Sinon on simule 'nbSimulation' parties aléatoires
                count=0; win=false;
                grid.addPion(color, col);                   //Ajout d'un Pion de couleur 'color' à la colonne 'col'
                if (!grid.isFull() && grid.gameFinished()==0)//Si la partie n'est pas finie (grille non pleine et pas encore de gagnant)
                    win = simulRandom(grid, color, false);   //cf. simulRandom()
                else
                    win = grid.gameFinished()==color.numPlayer();//Si la partie est finie, on renvoie vraie si le gagnant possède la couleur en entrée
                grid.removePion(col);
                if (win) count++;                           //On compte le nombre de parties gagnées
            }
        }
        if (count>countmax){                             //On stocke la colonne où il y a le plus de parties gagnées
            countmax=count;
            colmax=col;
        }
    }
    return colmax;
}
/* Simule une partie aléatoire à partir d'une position donnée de la grille
 * return true si la partie est gagné par le joueur ayant la couleur color
 */
private boolean simulRandom(Grid grid, Color color, boolean turnIA){
    //Raccourci, si il a un coup gagnant et que c'est le tour de l'IA, renvoie true
    //coup gagnant et tour de l'adversaire, renvoie false
    Color colorturn = turnIA ? color : Color.getOther(color);
    if (grid.winningMove(colorturn)!=-1){
        return turnIA;
    }
     
    boolean win;
    int colrandom=randomCol(grid);                      //cf. randomCol()
    grid.addPion(colorturn, colrandom);                 //Ajout d'un Pion dans la couleur aléatoire
    if (grid.gameFinished()!=0 || grid.isFull())        //Check si la partie est finie
        win = grid.gameFinished()==color.numPlayer();   //Si oui, win=true si l'IA a gagné
    else
        win = simulRandom(grid,color,!turnIA);          //Sinon, on simule un tour de plus
    grid.removePion(colrandom);
     
    return win;
}
    /* Renvoie une colonne aléatoire parmi celles de la grille qui ne sont pas pleines
     */
    private int randomCol(Grid grid){
        Random rand = new Random();
        ArrayList<Integer> colAvailable = new ArrayList<Integer>();
        for (int col=0; col<grid.getBoard()[0].length; col++){
            if (!grid.columnFull(col))
                colAvailable.add(colAvailable.size(), col);;
        }
        return colAvailable.get(rand.nextInt(colAvailable.size()));
    }
}
