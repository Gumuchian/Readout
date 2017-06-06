#include <iostream>
#include <math.h>
#include <Channel.h>

using namespace std;

int main()
{
    Channel ch0(pow(2,9),pow(2,18),pow(2,1));
    int i;
    for (i=0;i<100;i++){
        ch0.sumPolar();
        ch0.computeLC_TES();
        ch0.computeBBFB();
    }
    return 0;
}
