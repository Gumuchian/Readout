#include "Pixel.h"
#include "BBFB.h"
#include "TES.h"
#include <math.h>
#include <random>
#include "ressources.h"

Pixel::Pixel()
{

}

Pixel::Pixel(double frequence, double frequence_ideale, int phase_initiale):frequence(frequence)
{
    // les attributs compt(R_I,R_Q ...) sont les compteurs pour la table DDS
    comptR_I=phase_initiale%(Npt*interpolation);
    comptR_Q=(comptR_I+(Npt*interpolation)/4)%(Npt*interpolation);
    comptD_I=((Npt*interpolation)-((int)((Npt*interpolation)*rtd*(frequence_ideale/fe))%(Npt*interpolation))+phase_initiale)%(Npt*interpolation);
    comptD_Q=(comptD_I+(Npt*interpolation)/4)%(Npt*interpolation);
    pas=(int)round((Npt*interpolation)*(frequence_ideale/fe));
    feedback=new double[rtd+1];
    int i;
    for (i=0;i<rtd;i++){
        feedback[i]=0;
    }
}

double Pixel::getfeedback()
{
    return feedback[rtd];
}

double Pixel::getmodule()
{
    return bbfb.module();
}

double Pixel::computeLC()
{
    return tes.computeLCTES(frequence);
}

//computeBBFB prend en parametre les signaux de modulation/demodulation, l'entrée du SQUID et le nombre de point de la table DDS
void Pixel::computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    bbfb.compute_feedback(demoduI,remoduI,demoduQ,remoduQ,input);
    // update des compteurs
    comptR_I=(comptR_I+pas)%(Npt*interpolation);
    comptD_I=(comptD_I+pas)%(Npt*interpolation);
    comptR_Q=(comptR_Q+pas)%(Npt*interpolation);
    comptD_Q=(comptD_Q+pas)%(Npt*interpolation);
    int i;
    for (i=rtd;i>0;i--){
        feedback[i]=feedback[i-1];
    }
    feedback[0]=bbfb.getfeedback();
}

int Pixel::getcomptD_I()
{
    return comptD_I;
}

int Pixel::getcomptD_Q()
{
    return comptD_Q;
}

int Pixel::getcomptR_I()
{
    return comptR_I;
}

int Pixel::getcomptR_Q()
{
    return comptR_Q;
}

void Pixel::setinputLC(double input)
{
    tes.setbias(input);
}

double Pixel::getbiasm()
{
    return tes.getbiasm();
}

void Pixel::setI(double p)
{
    tes.setI(p);
}
