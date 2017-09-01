#include "TES.h"
#include <math.h>
#include <fstream>
#define PI 3.1415926535

typedef double (*ptrm) (double,double,double);

TES::TES()
{
    R0=0.001;
    T0=0.09;
    I0=51.5*pow(10,-6);
    Tes=T0;
    Po=0;
    R=R0;
    I=I0;
    V=51.5*pow(10,-9);
    alpha=75;
    beta=1.25;
    biasm[0]=0;biasm[1]=0;biasm[2]=0;
    bias[0]=0;bias[1]=0;bias[2]=0;
}

// derivee de T du TES
double TES::dTes(double Tes, double Pj, double Po)
{
    double G=115.0*pow(10,-12);
    double K=G/(3*pow(Tes,2));
    double C=0.8*pow(10,-12);
    double Tbath=0.055;
    return (Po+Pj-K*(pow(Tes,3)-pow(Tbath,3)))/C;
}

// derivee de I traversant le TES
double TES::dI(double I, double V, double R)
{
    double L=121*pow(10,-9);
    double Rl=60*pow(10,-6);
    return (V-I*Rl-I*R)/L;
}

// Solveur Runge Kutta 4 à pas constant
double TES::RK4(ptrm f, double dt, double y0, double y1, double y2)
{
    double k1,k2,k3,k4;
    k1=f(y0,y1,y2);
    k2=f(y0+dt/2*k1,y1,y2);
    k3=f(y0+dt/2*k2,y1,y2);
    k4=f(y0+dt*k3,y1,y2);
    return y0+dt/6*(k1+2*k2+2*k3+k4);
}

double TES::computeLCTES(double freq, double fe)
{
    double L=2*pow(10,-6),
    //Ccar=(1/(4*pow(PI,2)*L*pow(freq,2)))/1.02682,
    Ccar=13.0*pow(10,-9),
    Ccp=Ccar/100.0,
    TR=4.08,
    A=Ccp,
    B=pow(TR,2)*R0*(Ccar+Ccp),
    C=L*(Ccar+Ccp);

    /*ptrm ptrdT,ptrdI;
    ptrdT=&TES::dTes;
    ptrdI=&TES::dI;
    Pj=pow(51.5*pow(10,-9),2)/R;
    // Resolution des equa diff
    I=RK4(ptrdI,1.0/fe,I,V,R);
    Tes=RK4(ptrdT,1.0/fe,Tes,Pj,Po);
    // Update de R du TES
    R=R0+alpha*R0/T0*(Tes-T0)+beta*R0/I0*(I-I0);*/

    // Calcul de l'effet du LC
    bias[2]=bias[2]/(pow(2,18)-1);
    biasm[2]=(-(2-8*C*pow(fe,2))*biasm[1]-(1-2*fe*B+4*pow(fe,2)*C)*biasm[0]+2*fe*A*(bias[2]-bias[0]))/(2*fe*B+1+4*C*pow(fe,2));
    biasm[0]=biasm[1];
    biasm[1]=biasm[2];
    bias[0]=bias[1];
    bias[1]=bias[2];
    //biasm est normalise pour que le transitoire soit à 1 en amplitude (facteur de normalisation 0.5941)
    return biasm[2]*I/0.5941402124*sqrt(2)/TR;
}

void TES::setbias(double biass)
{
    bias[2]=biass;
}

double TES::getI()
{
    return I;
}

void TES::setPo(double P)
{
    Po=P;
}

double TES::getbiasm()
{
    return biasm[2];
}

void TES::setI(double p)
{
    I=p;
}
