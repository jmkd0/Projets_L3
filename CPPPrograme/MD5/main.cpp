#include <iostream>
#include <chrono>
#include <thread>
#include "md5.h"
 
using std::cout; using std::endl;
 using namespace std; 

//Tester le code avec la commande: 
//  g++ main.cpp md5.cpp -o md5_sample && ./md5_sample
//g++ -std=c++14 -pthread main.cpp md5.cpp -o md5_sample && ./md5_sample
bool trouve=false;
string key="45950e8a33d57cc2db70cb5f67a62d3a";

void Parcours(string chaine, string mot, int n, int k, int init, int fin, int num){
  static int t=k;
  int i;
  if(trouve==false){
	  if(md5(mot)==key){ 
       	cout<<mot<<" par le thread numero "<<num<<endl; 
  		trouve=true;
  		return;
      } 
  if(k==t){
      i=init;
      n=fin;
  }else{
      i=0;
      n=chaine.size();
      }  
   if(k>0){
     for(;i<n; i++){
          string mot1;  
           mot1=mot+chaine[i];
       Parcours(chaine, mot1, n, k-1,init, fin, num);
       }
   }
  }
}
int main(int argc, char *argv[]){
    string chaine="abcdefghijklmnopqrstuvwxyz";
    chaine+="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    chaine+="1234567890";
    //cout<<md5("ptdr");
	auto start=chrono::high_resolution_clock::now();
//Parcours(chaine, "",chaine.size(),4,0,62);
thread tre1(Parcours,chaine, "",chaine.size(),4,0,14,1);
thread tre2(Parcours,chaine, "",chaine.size(),4,15,30,2);
thread tre3(Parcours,chaine, "",chaine.size(),4,31,46,3);
thread tre4(Parcours,chaine, "",chaine.size(),4,47,62,4);
tre1.join();
tre2.join();
tre3.join();
tre4.join();
double dure=chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()*1e-3;
cout<<"\nVotre programme a durée: "<<dure<<" secondes";
cout<<endl<<"End";
	
	

    return 0;
}