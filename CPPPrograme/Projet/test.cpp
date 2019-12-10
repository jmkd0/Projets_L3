#include <iostream>
#include <math.h> 
using namespace std;
double pi(int n){
    double somme=0 ;
    for(int k=0; k<=n; k++){
        somme+=((double)4/(8*k+1)-(double)2/(8*k+4)-(double)1/(8*k+5)-(double)1/(8*k+6))/pow(16,k);
    }
    return somme;
}
int main(){
    int n=8;
    double d=pi(n);
    int a=(int)(d*pow(10,n+1))-10*(int)(d*pow(10,n));
    cout<<a;
}