#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <thread>
#include <string>
#include <chrono>
#include <string.h>
#include <mutex>
#include <ctime>
#include <gmp.h>
using namespace std;
mutex mute;
long val_precision;
mpf_t pi_valeur;
/* Calcule des décimales de pi avec la méthode BBP: Bailey-Borwein-Plouffe */

/* La fonction "calcule_pi_k" sert juste à 
calculer le k-ième terme de la somme de BBP
puis retourne dans pi_k la résultat obtenu*/
void calcule_pi_k(mpf_t pi_k, long k){
    mpf_t v1;
     mpf_init_set_d(v1,1);
        mpf_t  a, b, c, d, v16;     mpf_init_set_d( v16, 16);
        mpf_init_set_d(a, 8);     mpf_init_set_d(b, 8);    mpf_init_set_d(c, 8);  mpf_init_set_d(d, 8); 
        mpf_mul_ui(a, a, k);      mpf_mul_ui(b, b, k);     mpf_mul_ui(c, c, k);   mpf_mul_ui(d, d, k);
        mpf_add_ui(a, a, 1);      mpf_add_ui(b, b, 4);     mpf_add_ui(c, c, 5);   mpf_add_ui(d, d, 6);
        mpf_div(a, v1, a);        mpf_div(b, v1, b);       mpf_div(c, v1, c);     mpf_div(d, v1, d);
        mpf_mul_ui(a, a, 4);      mpf_mul_ui(b, b, 2);
        mpf_sub(a, a, b);         mpf_sub(a, a, c);        mpf_sub(a, a, d);
        mpf_pow_ui(v16, v16, k);  mpf_div(v16, v1, v16);
        mpf_mul(a, a, v16);
        mpf_set(pi_k, a);
        mpf_clear(a);   mpf_clear(b);   mpf_clear(c);   mpf_clear(d);   mpf_clear(v16);
}
/* La fonction "appelThread" set à éffectuer la somme des termes de BBP  */
void appelThread(int num_thead, int nbre_thread, long limite_pi){
    int k=num_thead;
    mpf_t  pi_k;
    mpf_init( pi_k );
    while(k<limite_pi){
        calcule_pi_k(pi_k, k-1);
        mute.lock();
        mpf_add(pi_valeur, pi_valeur, pi_k);
        mute.unlock();
        k+=nbre_thread;   
    }
}
void creerFichier(long limite_pi){
     string file_name = "resultat_19003239_" + to_string( limite_pi); // creation du nom de fichier
     ofstream fichier( file_name.c_str() );
    mp_exp_t exp;
    char* str;
    char char_flor[limite_pi+2];
   
    str=mpf_get_str(NULL,&exp,10,limite_pi+2, pi_valeur);              //convertion des décimaux de pi en char
    strcpy(char_flor, str);
    int i=1, new_line=2;
    if( fichier ){
         fichier<<"3.";
        while(i <= limite_pi){
            fichier<<char_flor[i]; 
            new_line++;
            if(!(new_line % 10)) fichier<<" ";
            if(new_line==100){                                          //Limiter le nombre de caractere à 100 sur une ligne
                fichier<<endl; new_line=0;
            }
            i++; 
        }

    }
         
}
int main(){
    vector<thread>  thr;
    long limite_pi;
    int nbre_thread;
    cout<<"Entrer la limite des décimales de pi: "; cin>>limite_pi; 
    cout<<"Entrer le nombre de thred: ";            cin>>nbre_thread; 
    /* Calcule du nombe de bits nécessaire pour stocker 
    ce nombre "limite_pi" de décimal de pi (3.33 fois le nombre de décimal) 
    mais je l'arrondi à 4 */
    long val_precision=4*limite_pi;

    mpf_set_default_prec( val_precision );  //initialisation de la précision de calcule
    mpf_init_set_d( pi_valeur, 0);
    
    //Début de comptage de durée puis parallélisation des appelles
    auto start = chrono::high_resolution_clock::now();

        for(int k=0; k<nbre_thread; k++){
            thr.push_back( thread (appelThread, k, nbre_thread, limite_pi));
         }
        for( int i=0; i < nbre_thread; i++){
            thr[i].join();
        }
         //Finde comptage de durée
    auto stop = chrono::high_resolution_clock::now();
   
    creerFichier(limite_pi);                //Appel de la fonction de création du fichier
     double dur = chrono::duration_cast <chrono::microseconds>(stop - start).count()*1e-6;

    mpf_clear(pi_valeur);                   //Libération de la mémoire
    cout<<"Le programme a duré: "<<dur<<" secondes"<<endl;

    return 0;
}