#include "Channel.h"

Channel::Channel()
{
    int i;
    for (i=0;i<40;i++){
        ch.push_back(Pixel(1000000+i*100000,0,0,1,4));
    }
}
