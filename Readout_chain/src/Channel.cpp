#include "Channel.h"
#include "DDS.h"

Channel::Channel()
{

}

Channel::Channel(int taille, int precision, int interp):dds(taille,precision,interp)
{
    int i;
    for (i=0;i<40;i++){
        ch.push_back(Pixel(1000000+i*100000,0,0,1,4,1,1));
    }
}

float Channel::sumPolar()
{
    int i;
    float sum=0;
    for (i=0;i<(int)ch.size();i++){
        sum=sum+dds.getvalue(ch[i].getcount());
    }
    return sum;
}
