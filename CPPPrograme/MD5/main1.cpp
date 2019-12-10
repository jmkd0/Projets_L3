#include <iostream>
#include "md5.h"
 
using std::cout; using std::endl;
 using namespace std; 

//Tester le code avec la commande: 
//  g++ main.cpp md5.cpp -o md5_sample && ./md5_sample


string key="45950e8a33d57cc2db70cb5f67a62d3a";

int main(int argc, char *argv[]){
    
	
	string chaine="abcdefghijklmnopqrstuvwxyz";
    chaine+="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    chaine+="1234567890";

	
	cout << "md5 of 'hello': " << md5("ptdr") << endl;
    string al;
    string test="45950e8a33255cc2db70cb5f67a62d3a";

        					    			
   string alph("abcdefghijklmnopqrstuvwxyz0123456789");
	int cpt=0;
    int i=0, j=0, k=0, l=0;
    																																					
    while(i<36){	
    	al+=alph[i];
    	while(j<36){
    		al+=alph[j];
    		while(k<36){
    			al+=alph[k];
    			while(l<36){
    				 al+=alph[l];
					 cout<<cpt++<<endl;
					//  cout <<  md5(al);
    				if(md5(al).compare(test)==0){

    					cout <<al + " TROUVER";
    					   cout <<  md5(al);
    				}
    				l++;
    			}
    			l=0;
    			k++;
    		}
    		k=0;
    		j++;
    	}
    	j=0;
    	i++;
    }

    return 0;
}