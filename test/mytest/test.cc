#include "sim_api.h"
#include <random>
#include <iostream>
int main()
{
    SimRoiStart();
    SimMarker(5, 1);
    int *a = new int[100000];
    int *b = new int[100000];
    int *c = new int[100000];
    std::cout << a << " " << b << " " << c << std::endl;
    SimRoiStart();
    SimMarker(3, 2);
    for (int i = 0; i < 10000000; i++)
    {
      
        a[i%10000] = i - 1;

        b[i%10000] = i + 1;

        b[i%10000] = b[i%10000] + a[i%10000];
        SimMarker(1, 1);
        c[i%10000] = a[i%10000] + b[i%10000];
        SimMarker(2, 1);

        SimMarker(3, 1);
        if ((c[i%10000]%a[i%10000])%2==0)
        {
            a[1] = 2;
        }
        else
        {
            a[1] = 1;
        }
        SimMarker(3, 2);
    }

    SimRoiEnd();
    return 0;
}
