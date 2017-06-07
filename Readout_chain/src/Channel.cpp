#include "Channel.h"
#include "DDS.h"
#include <math.h>

Channel::Channel()
{

}

Channel::Channel(int taille, int precision, int interp):dds(taille,precision,interp)
{
    int i;
    for (i=0;i<1;i++){
        ch.push_back(Pixel(1000000+i*100000,0,0,1,4,20000000,taille*interp));
    }
}

void Channel::sumPolar()
{
    int i;
    double sum=0;
    for (i=0;i<(int)ch.size();i++){
        sum=sum+dds.getvalue(ch[i].getcount());
    }
    for (i=0;i<(int)ch.size();i++){
        ch[i].setinputLC(sum);
    }
}

void Channel::computeLC_TES()
{
    int i;
    double sum=0;
    for (i=0;i<(int)ch.size();i++){
        sum=sum+ch[i].computeLC();
    }
    input=sum;
}

void Channel::computeBBFB()
{
    int i;
    double dac,feedback=0;
    int taille=pow(2,10);
    for (i=0;i<(int)ch.size();i++){
        feedback=feedback+ch[i].getfeedback();
    }
    dac=0.5*80*0.0017/(5.8*pow(10,-6))*(input-feedback);
    for (i=0;i<(int)ch.size();i++){
        ch[i].computeBBFB(ch[i].getcount(),ch[i].getcount(),ch[i].getcount()+taille/4,ch[i].getcount()+taille/4,dac);
    }
}

