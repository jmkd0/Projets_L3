#include <iostream>
#include <thread>
#include <mutex>
#include "unistd.h"



#include <iostream>
#include <thread>
#include <mutex>

std::mutex mymutex;
void Max(int tab[], int debut, int fin){
    int max=0;
    mymutex.lock();
    for(int i=debut; i<=fin; i++){
        if(tab[i]>max){
            max=tab[i];
        }
    }
    mymutex.unlock();
    std::cout<<max<<"   \n";
    
}




int main(){
    int tab[]={1,19,56,8,34,100,45,78,17,44};
    std::thread t1(Max,tab,0, 4);
    std::thread t2(Max,tab,5, 9);
    t1.join();
     t2.join();
    
    
}