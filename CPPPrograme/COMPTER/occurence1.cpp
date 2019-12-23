#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <fstream> 
#include <chrono>


using namespace std;
int cpt=0;
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

vector<string> motsfichier(){
    vector<string> vecteur;
    ifstream fichier("file.txt");
    if ( fichier ){ 
        string mot;
        while (fichier>>mot){ 
            vector<string> vec=split(mot,".’,-0123456789");
            for(auto a:vec){       
           if(a.size()>2)vecteur.push_back(a);
            }
        } 
    } 
    return vecteur;
}

void occurrence(vector<string> vecteur, int k, int m){
    vector<pair<string, int>> occur;
    int i=k;
    for(; i<m; i++){
        int j=0;
        while(j<occur.size()&&vecteur[i]!=occur[j].first) j++;
        if(j==occur.size()){
            occur.push_back(make_pair(vecteur[i],1));
        }else{
            occur[j].second+=1; 
        }
    }
      for(int i=0; i<occur.size(); i++){
        cout<<occur[i].first<<"\t\t\t\t\t\t"<<occur[i].second<<"\n";
        cpt++;
    }
 
    
}

int main(){
     int n;
     cout<<"Entrer le nombre de thread: ";cin>>n;
	 auto start=chrono::high_resolution_clock::now();
     vector<thread> st;
     vector<string> vecteur=motsfichier();
    
     int k=(int)vecteur.size()/n;

   for(int i=0; i<n-1; i++){
        st.push_back(thread (occurrence,vecteur,k*i,k*(i+1)));
    }
    st.push_back(thread (occurrence,vecteur,k*(n-1),(int)vecteur.size()));
    for(int i=0; i<n; i++){
        st[i].join();
    }
auto stop=chrono::high_resolution_clock::now();
double dur=chrono::duration_cast<chrono::microseconds>(stop-start).count()*1e-6;
   cout<<"Vous avez en tout: "<<cpt<<" mots";
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