#include "Channel.h"
#include "DDS.h"
#include <math.h>
#include <fstream>
#include <string>
#include <random>
#include "ressources.h"

Channel::Channel():dds(Npt,Npr,interpolation)
{
    int i;
    input=0;
    std::string str;
    char* ptr;
    double frequency[40];
    std::ifstream file("Frequency.txt", std::ios::out);
    if(file)
    {
        for (i=0;i<40;i++)
        {
            getline(file,str);
            frequency[i]=strtod(str.c_str(),&ptr);
        }
    }
    for (i=0;i<Npix;i++){
        ch.push_back(Pixel(1000000.0+i*100000.0,frequency[i],trunc(pow(i,2)*(Npt*interpolation)/(2*Npix))));
    }
    feedback = new double[delay+1];
    for (i=0;i<delay+1;i++)
    {
        feedback[i]=0;
    }
}

double Channel::sumPolar()
{
    int i;
    double sum=0;
    for (i=0;i<Npix;i++){
        sum=sum+dds.getvalue(ch[i].getcomptR_I());
    }
    for (i=0;i<Npix;i++){
        ch[i].setinputLC(sum);
    }
    return sum;
}

void Channel::computeLC_TES()
{
    int i;
    double sum=0;
    for (i=0;i<Npix;i++)
    {
        sum=sum+ch[i].computeLC();
    }
    input=sum;
}

double Channel::computeBBFB()
{
    int i;
    double adc;
    std::normal_distribution<double> bbg(0.0,LNA_dsl*sqrt(Ba));
    feedback[0]=0;
    for (i=0;i<Npix;i++)
    {
        feedback[0]=feedback[0]+ch[i].getfeedback();
    }
    feedback[0]=G_filter*PE/pow(2,DAC_bit)*trunc(Gb*feedback[0]/Npr);
    adc=G_filter*(G_LNA*G_SQUID*(input-0.1*feedback[delay])+bbg(gen));
    for (i=0;i<Npix;i++)
    {
        ch[i].computeBBFB(dds.getvalue(ch[i].getcomptD_I()),dds.getvalue(ch[i].getcomptR_I()),dds.getvalue(ch[i].getcomptD_Q()),dds.getvalue(ch[i].getcomptR_Q()),trunc(pow(2,ADC_bit)*adc));
    }
    for (i=delay;i>0;i--)
    {
        feedback[i]=feedback[i-1];
    }
    return input;
}

 double Channel::getinput()
 {
     return input;
 }

 double Channel::getfck()
 {
     return feedback[delay];
 }

 double Channel::getmod()
 {
     return ch[0].getmodule();
 }

 void Channel::setI(double p)
 {
     ch[0].setI(p);
 }
