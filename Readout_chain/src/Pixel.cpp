#include "Pixel.h"
#include "BBFB.h"
#include "TES.h"
#include <math.h>
#include <random>

Pixel::Pixel()
{

}

// amplitude est inutilisée, le gain intervient avant l'integrateur, fe la fréquence d'échantillonnage, N la taille de la table DDS
Pixel::Pixel(double frequence, double frequence_ideale, int phase_initiale, int phase_retard, int amplitude, int gain, double fe, int N, int precision, int retard): frequence(frequence),frequence_ideale(frequence_ideale),phase_initiale(phase_initiale),phase_retard(phase_retard),amplitude(amplitude),bbfb(gain),fe(fe),precision(precision),retard(retard)
{
    // les attributs compt(R_I,R_Q ...) sont les compteurs pour la table DDS
    comptR_I=phase_initiale%N;
    comptR_Q=(comptR_I+N/4)%N;
    comptD_I=(N-((int)(N*retard*(frequence_ideale/fe))%N)+phase_initiale)%N;
    comptD_Q=(comptD_I+N/4)%N;
    pas=(int)round(N*(frequence_ideale/fe));
    feedback=new double[retard+1];
    int i;
    for (i=0;i<retard;i++){
        feedback[i]=0;
    }
}

double Pixel::getfeedback()
{
    return feedback[retard];
}

double Pixel::getmodule()
{
    return bbfb.module();
}

double Pixel::computeLC()
{
    return tes.computeLCTES(frequence,fe,precision);
}

//computeBBFB prend en parametre les signaux de modulation/demodulation, l'entrée du SQUID et le nombre de point de la table DDS
void Pixel::computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input, int precision, int N)
{
    bbfb.compute_feedback(demoduI,remoduI,demoduQ,remoduQ,precision,input);
    // update des compteurs
    comptR_I=(comptR_I+pas)%N;
    comptD_I=(comptD_I+pas)%N;
    comptR_Q=(comptR_Q+pas)%N;
    comptD_Q=(comptD_Q+pas)%N;
    int i;
    for (i=retard;i>0;i--){
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

/*void Pixel::setPo(double P)
{
    tes.setPo(P);
}*/

int Pixel::getretard()
{
    return retard;
}

void Pixel::setI(double p)
{
    tes.setI(p);
}
