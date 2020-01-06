#include "sim_api.h"
#include<random>
#include<iostream>
int main(){
    SimRoiStart();
    SimMarker(5,2);
    int *a=new int[100000];
    int *b=new int[100000];
    int *c=new int[100000];
    std::cout<<a<<" "<<b<<" "<<c<<std::endl;
    for(int i=0;i<100000;i++){
        a[i]=i-1;
        SimMarker(5,1);
        b[i]=i+1;
        SimMarker(5,2);
   
        b[i]=b[i]+a[i];
        SimMarker(1,1);
        c[i]=a[i]+b[i];
        SimMarker(2,1);
        
        SimMarker(3,1);
        if(a[1]==1){
            a[1]=2;
        }else{
            a[1]=1;
        }
        SimMarker(3,2);

    }
    SimRoiEnd();    
    return 0;
}