#include <iostream>
#include <vector>
using namespace std;
void modif(vector<int> v){
    for(int i=0; i<4; i++)
        cout<<v[i]<<endl;
}
int main(){
    vector<int> v={4,6,9,1};
    modif (v);
    
    return 0;
}

/* int main() {
 //premier(10,20);
 vector<int> v={4,6,9,1};
// modif (v);
 itter(v,2);
 for(int i=0; i<4; i++){
     cout<<v[i]<<endl;
 } */