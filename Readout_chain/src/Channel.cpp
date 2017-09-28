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
    fck=0;
    slope=0;
    std::string str;
    char* ptr;
    double frequence[40];
    std::ifstream fichier("Frequences.txt", std::ios::out);
    if(fichier)
    {
        for (i=0;i<40;i++)
        {
            getline(fichier,str);
            frequence[i]=strtod(str.c_str(),&ptr);
        }
    }
    for (i=0;i<Npix;i++){
        ch.push_back(Pixel(1000000.0+i*100000.0,frequence[i],trunc(pow(i,2)*(Npt*interpolation)/(2*Npix))));
    }
}

// Calcul de la somme des bias et envoi de la somme des bias aux LC
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

// Calcul de la sortie des LC
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

// Calcul du BBFB
double Channel::computeBBFB()
{
    int i;
    double adc,feedback=0;
    //somme du feedback de chaque pixel
    std::normal_distribution<double> bbg(0.0,dsla*sqrt(Ba));
    for (i=0;i<Npix;i++)
    {
        feedback=feedback+ch[i].getfeedback();
    }
    /*G = gain du feedback
    0.5 = attenuation du filtre
    0.01/pow(2,15) = conversion du DAC
    pow(2,19) = troncation de 19 bits*/
    feedback=G_filter*PE/pow(2,DAC_bit)*trunc(Gb*feedback/Npr);
    //dac = entrée du DAC
    /*0.5 = attenuation du filtre
    80 = gain du LNA
    0.0017/(5.8*pow(10,-6)) = transimpedance du SQUID, facteur 0.1 sur feedback
    */
    adc=G_filter*(G_LNA*G_SQUID*(input-0.1*feedback)+bbg(gen));
    fck=feedback;
    // Calcul du feedback pour chaque pixel
    for (i=0;i<Npix;i++)
    {
        //dds.getvalue donne la valeur de la table DDS pour le compteur ch[i].getcompt(D_I(),D_Q(),R_I(),R_Q()) pour le pixel i, trunc(pow(2,12)*adc) : conversion de l'adc en numérique
        ch[i].computeBBFB(dds.getvalue(ch[i].getcomptD_I()),dds.getvalue(ch[i].getcomptR_I()),dds.getvalue(ch[i].getcomptD_Q()),dds.getvalue(ch[i].getcomptR_Q()),trunc(pow(2,ADC_bit)*adc));
    }
    return input;
}

 double Channel::getinput()
 {
     return input;
 }

 double Channel::getfck()
 {
     return fck;
 }

 double Channel::getmod()
 {
     return ch[0].getmodule();
 }

 void Channel::setI(double p)
 {
     ch[0].setI(p);
 }
