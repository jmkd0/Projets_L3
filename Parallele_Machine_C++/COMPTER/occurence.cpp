#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <fstream> 
#include <chrono>


using namespace std;

string separateur=".’, -0123456789";

vector<string> split(string str, string sp){
    vector<string> vec; int i=0;   
while(i<(int)str.size()){
     int k=i; 
   while(sp.find(str[i])==string::npos&&i<(int)str.size()) i++;
     string mot=str.substr(k,i-k);
   if(mot!="") vec.push_back(mot);
   i++;}
 return vec;
 }
void occurrence(int debut, int fin){
     ifstream fichier("file.txt");
     string ligne; int i=debut;
     while( getline( fichier,ligne ) && i<fin){
       if(i >= debut){
           vector<string> vec=split(ligne,".’, -0123456789");
           for(auto mot:vec){
               if(mot.size()>2){
                    int j=0;
                    while(j< occur.size() && mot != occur[j].first ) j++;
                    if(j==occur->size()){
                      occur->push_back(make_pair(mot,1));
                     }
                     else 
                        occur[j].second += 1;       
                }


            }
        }
         i++;
     }
    
}


int main(){
     int n;
     cout<<"Entrer le nombre de thread: ";cin>>n;
	 auto start=chrono::high_resolution_clock::now();
    vector<pair<string, int>>* occur;
     vector<thread> st;
     ifstream file("file.txt");
     string ligne;
     int nligne=0;
     while(getline(file,ligne)) nligne++;
     
     int k=nligne/n;

   for(int i=0; i<n-1; i++){

        st.push_back(thread (occurrence,&occur,k*i,k*(i+1)));
    }
    st.push_back(thread (occurrence,&occur,k*(n-1),nligne));
    for(int i=0; i<n; i++){
        st[i].join();
    }
    occurrence(occur,k*(n-1),nligne);
 for(int i=0; i<occur->size(); i++){
        cout<<occur->at(i).first<<"\t\t\t\t\t\t"<<occur->at(i).second<<"\n";
    }
    cout<<"taille "<<occur->size();
auto stop=chrono::high_resolution_clock::now();
double dur=chrono::duration_cast<chrono::microseconds>(stop-start).count()*1e-6;
cout<<"\n Duration fait       "<<dur<<"seconds"<<endl;
    return 0;
}  















































/*

bool is_readable( const std::string & file ){  
    std::ifstream fichier( file.c_str() );  
    return !fichier.fail();  


void Exemple() 
{ 
    using std::cout; 
    if ( is_readable( "test.txt" ) ){  
        cout << "Fichier existant et lisible.\n";  
    }else{  
        cout << "Fichier inexistant ou non lisible.\n";  
    }  
}

	return 0;
}*/