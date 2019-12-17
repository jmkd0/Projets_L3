#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <math.h>
#include <thread>
#include <string>
#include <chrono>
#include <string.h>
#include <mutex>
#include <math.h>
#include <gmp.h>
//#include </home/komlan/gmp/include/gmp.h>
#include <string.h>
void foo (mpz_t result, const mpz_t param, unsigned long n){
  unsigned long  i;
  mpz_mul_ui (result, param, n);
  for (i = 1; i < n; i++)
    mpz_add_ui (result, result, i*7);
}

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
int main (void){
    vector<thread>  thr;
    long limite_pi;
    int nbre_thread;
    cout<<"Entrer la limite des décimales de pi: "; cin>>limite_pi; 
    cout<<"Entrer le nombre de thred: ";            cin>>nbre_thread; 
 for(int k=0; k<nbre_thread; k++){
            thr.push_back( thread (appelThread, k, nbre_thread, limite_pi));
         }
        for( int i=0; i < nbre_thread; i++){
            thr[i].join();
        }
}
