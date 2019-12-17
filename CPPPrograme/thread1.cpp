#include <iostream>
#include <thread>
#include <mutex>

std::mutex mymutex;
void comp(int arg1, int arg2){
    int i=0;
    mymutex.lock();
    for(i=arg1; i<arg2; i++){
        std::cout<<i;
    }
    mymutex.unlock();
    std::cout<<i<<"\n";
}

int main(){
    std::thread t1(comp,0, 5);
    std::thread t2(comp,6, 10);
    t1.join();
    t2.join();
}