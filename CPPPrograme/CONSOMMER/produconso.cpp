#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <time.h>
using namespace std;


//Consommer(); Consommer();
/*Run with: g++ -std=c++14 -pthread pro_conso.cpp*/

vector<int> Liste={45,30,56,98,17};
int i=Liste.size();
void Produire(){
  	srand(time(NULL));
  
	while(i<=10){
        if(i<10){
          int pr=rand()%100+1;
          Liste.push_back(pr);
           cout<<"J'ai produit:\t\t"<<pr<<endl;
           this_thread::sleep_for(chrono::seconds(rand()%2+1)); 
                  i++;   
         }else{
          cout<<endl<< "Panier plein"<<endl;
           this_thread::sleep_for(chrono::seconds(1));
      }
    }
}



int Consommer(){
 
	while(i>=0){
        if(i>0){
          cout<<"J'ai consommé:\t\t"<<Liste[i-1]<<endl;
          Liste.pop_back();      
          this_thread::sleep_for(chrono::seconds(rand()%2+1));   
          i--;
         }else{
          cout<<endl<< "Panier vide"<<endl;
           this_thread::sleep_for(chrono::seconds(1));
      }
    }
}

int main(){
	
 
	auto start=chrono::high_resolution_clock::now();
//lignes de code à mesurer

while((double)chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-start).count()<5){
    std::thread t1(Produire);
    std::thread t2(Consommer);


    t1.join();
    t2.join();}
	return 0;
}