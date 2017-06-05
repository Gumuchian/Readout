#include <iostream>
#include <math.h>
#include <DDS.h>
#include <Pixel.h>

using namespace std;

int main()
{
    /*int i;
    DDS dds(pow(2,9),pow(2,18),pow(2,1));
    for (i=0;i<pow(2,10);i++){
        cout << dds.getvalue(i) << endl;
    }*/
    Pixel pixel(1,0,0,1,1);
    cout << pixel.getmodule() << endl;
    return 0;
}
