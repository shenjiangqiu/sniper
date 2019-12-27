#include "sim_api.h"
#include<random>
#include<iostream>
int main(){
    int *a=new int[1000];
    int *b=new int[1000];
    int *c=new int[1000];
    auto eg=std::default_random_engine();
    auto dist=std::uniform_int_distribution<int>(1,1000);

    for(int i=0;i<1000;i++){
        a[i]=dist(eg);
        b[i]=2*dist(eg);
        b[i]=b[i]+a[i];
        SimMarker(1,1);
        c[i]=a[i]+b[i];
        SimMarker(2,1);
    }
    for(int i=0;i<1000;i++)
        //std::cout<<"C["<<i<<"]="<<c[i]<<std::endl;
    return 0;
}