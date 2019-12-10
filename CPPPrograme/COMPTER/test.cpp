#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

void tab(vector<int> A){
A.push_back(67);
}
int main(){
vector<int> A={2,4};
tab(A);
cout<<A[2];

    return 0;
}