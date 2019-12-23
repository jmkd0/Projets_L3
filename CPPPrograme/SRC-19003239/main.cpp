#include <iostream>
#include <thread>
#include <fstream>
#include <set>
#include <cmath>
#include <chrono>
#include <vector>
#include <mutex>
using namespace std;
int cpt_nbre_premier;
mutex mute;
set <int>  listpremier;
void premiers( int min, int max ){
    
  for(int i = min; i <= max; i++){
     int q = 2;
     bool sortie = false;
        while( sortie == false && q <= (int)sqrt(i) ){
            if(!(i%q)) sortie = true;
            q++;
        }
        if( sortie == false ){
            mute.lock();
             listpremier.insert( i );
             cpt_nbre_premier++;
            mute.unlock();
        }
    }
    
}
void creerThread( int k, int nthread, int nlimite){
    vector<thread>  thr;
     thr.push_back(thread ( premiers, 2, k));
   for(int i=1; i<nthread-1; i++){
       thr.push_back( thread (premiers, k*i+1, k*(i+1)));
     }
     if( nthread != 1)
            thr.push_back( thread (premiers, k*(nthread-1) +1, nlimite));
    for( int i=0; i < nthread; i++){
        thr[i].join();
    }
}

/*On parcours la structure de donnée set en affichant ses valeurs
Arrivé au 600.000 ieme élément 
on ferme le fichier et 
créer un autre fichier contenant la suite
*/

void creerFichier(int nlimite){
     string file_name = "resultat_19003239_" + to_string( nlimite ); // creation du nom de fichier
     ofstream fichier( file_name.c_str() );
     int cpt=0;
     auto iterateur=listpremier.begin();
     while( cpt< 600000 && iterateur!=listpremier.end() ){               
     if( fichier ){
                fichier<< *iterateur <<endl;
                iterateur++;
                cpt++;
       }
       if(cpt==600000){
           fichier.close();
       string file_name1 = file_name+"_1"; 
       ofstream fichier1( file_name1.c_str() );
       while( iterateur!=listpremier.end() ){                
        if( fichier1 ){
                fichier1<< *iterateur <<endl;
                iterateur++;            
        }
       }
     }
    }
}
int main() {
     int nthread, nlimite;
     cout << "Entrer le nombre de thread: ";    cin>> nthread;
     cout<<"Entrer le nombre limite de nombre premier: "; cin>> nlimite;

       // On calcul la durée de recherche des nombres premiers

    auto start = chrono::high_resolution_clock::now();
                    int k = (int)nlimite/nthread;         // On calcule le pas de chaque thread par une division entière
                    creerThread( k , nthread, nlimite );  //appel de la fonction creerThread pour répartir l'intervalle de traitement pour chaque thread
    auto stop = chrono::high_resolution_clock::now();

    creerFichier(nlimite); // Création des fichiers contenant les nombres premiers 
   
    double dur = chrono::duration_cast <chrono::microseconds>(stop - start).count()*1e-6;
    cout <<" Vous avez en tout "<< cpt_nbre_premier <<" nombre premiers entre  0 et " << nlimite <<"."<< endl;
    cout <<"\n The duration is:      "<< dur <<" seconds."<< endl;
    return 0;

}