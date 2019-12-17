#include <iostream>
#include <thread>
#include <mutex>
#include "unistd.h"


int fct(int i){
    std::mutex mutex;
    mutex.lock();
    std::cout<<i<<'\n'; 
    sleep(3);
    std::cout<<i*i<<'\n';
    mutex.unlock();
    return i*2;

}
int main(){
    std::thread t1(fct,5);
    t1.join();
    fct(2);
    return 0;
}