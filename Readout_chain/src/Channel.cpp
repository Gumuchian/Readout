#include "Channel.h"
#include "DDS.h"
#include <math.h>
#include <fstream>
#include <string>
#include <random>

Channel::Channel()
{

}

/* Constructeur:
    _ N = nombre de pixels
    _ taille = taille de la table DDS
    _ precision = maximum des valeurs stockées dans la table DDS
    _ interp = nombre de points d'interpolation
    _ retard = retard de boucle exprimé en nombre de pas de simulations*/
Channel::Channel(int N, int taille, int precision, int interp, int retard):N(N),dds(taille,precision,interp)
{
    int i;
    input=0;
    fck=0;
    Ba=10000000;
    dsla=1.0*pow(10,-13);
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
    for (i=0;i<N;i++){
        //ch.push_back(Pixel(20000000.0/(taille*interp)*round((1000000.0+i*100000.0)*taille*interp/20000000.0),trunc(pow(i,2)*(taille*interp)/(2*N)),0,1,5000,20000000.0,taille*interp,1));
        //ch.push_back(Pixel(974500.0+i*100000.0,trunc(pow(i,2)*(taille*interp)/(2*N)),0,1,5000,20000000.0,taille*interp,1));
        ch.push_back(Pixel(1000000.0+i*100000.0,frequence[i],trunc(pow(i,2)*(taille*interp)/(2*N)),0,1,5000,20000000.0,taille*interp,1));
    }
}

// Calcul de la somme des bias et envoi de la somme des bias aux LC
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

// Calcul de la sortie des LC
void Channel::computeLC_TES()
{
    int i;
    double sum=0;
    for (i=0;i<N;i++){
        sum=sum+ch[i].computeLC();
    }
    input=sum;
}

// Calcul du BBFB
void Channel::computeBBFB()
{
    int i;
    double adc,G=37000,feedback=0;
    //somme du feedback de chaque pixel
    std::normal_distribution<double> bbg(0.0,dsla*sqrt(20000000.0));
    for (i=0;i<N;i++){
        feedback=feedback+ch[i].getfeedback();
    }
    /*G = gain du feedback
    0.5 = attenuation du filtre
    0.01/pow(2,15) = conversion du DAC
    pow(2,19) = troncation de 19 bits*/
    feedback=0.5*0.01/pow(2,15)*G*feedback/pow(2,19);
    //dac = entrée du DAC
    /*0.5 = attenuation du filtre
    80 = gain du LNA
    0.0017/(5.8*pow(10,-6)) = transimpedance du SQUID, facteur 0.1 sur feedback
    */
    adc=0.5*80*0.0017/(5.8*pow(10,-6))*(input-0.1*feedback)+bbg(gen)*0.5;
    fck=feedback;
    // Calcul du feedback pour chaque pixel
    for (i=0;i<N;i++)
    {
        //dds.getvalue donne la valeur de la table DDS pour le compteur ch[i].getcompt(D_I(),D_Q(),R_I(),R_Q()) pour le pixel i, trunc(pow(2,12)*adc) : conversion de l'adc en numérique
        ch[i].computeBBFB(dds.getvalue(ch[i].getcomptD_I()),dds.getvalue(ch[i].getcomptR_I()),dds.getvalue(ch[i].getcomptD_Q()),dds.getvalue(ch[i].getcomptR_Q()),trunc(pow(2,12)*adc),pow(2,16));
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

 void Channel::setI(double p)
 {
     ch[0].setI(p);
 }
