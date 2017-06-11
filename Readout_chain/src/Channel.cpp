#include "Channel.h"
#include "DDS.h"
#include <math.h>

Channel::Channel()
{

}

Channel::Channel(int N, int taille, int precision, int interp, int retard):N(N),dds(taille,precision,interp)
{
    int i;
    input=0;
    fck=0;
    for (i=0;i<N;i++){
        ch.push_back(Pixel(3900000+i*100000,trunc(pow(i,2)*(taille*interp)/(2*N)),0,1,4,20000000,taille*interp,1));
    }
}

double Channel::sumPolar()
{
    int i;
    double sum=0;
    for (i=0;i<N;i++){
        sum=sum+dds.getvalue(ch[i].getcomptR_I());
    }
    for (i=0;i<N;i++){
        ch[i].setinputLC(sum);
    }
    return sum;
}

void Channel::computeLC_TES()
{
    int i;
    double sum=0;
    for (i=0;i<N;i++){
        sum=sum+ch[i].computeLC();
    }
    input=sum;
}

void Channel::computeBBFB()
{
    int i;
    double dac,G=1000,feedback=0;

    for (i=0;i<N;i++){
        feedback=feedback+ch[i].getfeedback();
    }
    feedback=0.5*0.01/pow(2,15)*G*feedback/pow(2,19);
    dac=0.5*80*0.0017/(5.8*pow(10,-6))*(input-0.1*feedback);
    fck=feedback;
    for (i=0;i<N;i++)
    {
        ch[i].computeBBFB(dds.getvalue(ch[i].getcomptD_I()),dds.getvalue(ch[i].getcomptR_I()),dds.getvalue(ch[i].getcomptD_Q()),dds.getvalue(ch[i].getcomptR_Q()),trunc(pow(2,12)*dac),pow(2,16));
    }
}
 double Channel::getinput()
 {
     return input;
 }

 double Channel::getfck()
 {
     return fck;
 }

 void Channel::setPo(double P)
 {
     ch[0].setPo(P);
 }

double Channel::getmod()
 {
     return ch[0].getmodule();
 }
