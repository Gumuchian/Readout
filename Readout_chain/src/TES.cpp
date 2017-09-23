#include "TES.h"
#include <math.h>
#include <fstream>
#include <random>
#include "ressources.h"
#include <iostream>

TES::TES():gen((std::random_device())())
{
    I=I0;
    biasm[0]=0;biasm[1]=0;biasm[2]=0;
    bias[0]=0;bias[1]=0;bias[2]=0;
    bbfi[0]=0;bbfo[0]=0;bbfo[1]=0;
}

double TES::computeLCTES(double freq)
{
    double Ccar=(1/(4*pow(PI,2)*Lc*pow(freq,2))),
    Ccp=Ccar/100.0,
    A=Ccp,
    B=pow(TR,2)*R0*(Ccar+Ccp),
    C=Lc*(Ccar+Ccp);
    // Calcul de l'effet du LC
    bias[2]=bias[2]/Npr;
    biasm[2]=(-(2-8*C*pow(fe,2))*biasm[1]-(1-2*fe*B+4*pow(fe,2)*C)*biasm[0]+2*fe*A*(bias[2]-bias[0]))/(2*fe*B+1+4*C*pow(fe,2));
    biasm[0]=biasm[1];
    biasm[1]=biasm[2];
    bias[0]=bias[1];
    bias[1]=bias[2];
    std::normal_distribution<double> bbg(0,dsl*sqrt(Btes));
    bbfi[1]=bbg(gen);
    bbfo[1]=(bbfi[1]+bbfi[0]+(fe/(PI*fc)-1)*bbfo[0])/(fe/(PI*fc)+1);
    bbfi[0]=bbfi[1];
    bbfo[0]=bbfo[1];
    //biasm est normalise pour que le transitoire soit � 1 en amplitude (facteur de normalisation 0.5941)
    return biasm[2]*(I*sqrt(2)+bbfo[1])/0.481859849392335/TR;
}

void TES::setbias(double biass)
{
    bias[2]=biass;
}

double TES::getI()
{
    return I;
}

double TES::getbiasm()
{
    return biasm[2];
}

void TES::setI(double p)
{
    I=p;
}
