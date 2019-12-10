#include <iostream>
using namespace std;
string key="45950e8a33255cc2db70cb5f67a62d3a";

void Parcours(string chaine, string mot, int n, int k, int init, int fin){
  static int t=k;
  int i;
  if(md5(mot)==key) cout<<mot;

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
       Parcours(chaine, mot1, n, k-1,init, fin);
       }
   }
    
}

int main(){
    string chaine="abcdefghijklmnopqrstuvwxyz";
    chaine+="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    chaine+="1234567890";
    
Parcours(chaine, "",chaine.size(),4,0,62);
    return 0;
}