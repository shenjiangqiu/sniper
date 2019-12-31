#include "sim_api.h"
#include<random>
#include<iostream>
int main(){
    SimRoiStart();
    int *a=new int[10];
    int *b=new int[10];
    int *c=new int[10];
    std::cout<<a<<" "<<b<<" "<<c<<std::endl;
    for(int i=0;i<10;i++){
        a[i]=i-1;
        b[i]=i+1;
   
        b[i]=b[i]+a[i];
        SimMarker(1,1);
        c[i]=a[i]+b[i];
        SimMarker(2,1);


    }
    SimRoiEnd();    
    return 0;
}