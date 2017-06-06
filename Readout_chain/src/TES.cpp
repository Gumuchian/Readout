#include "TES.h"
#include <math.h>

TES::TES()
{
    //ctor
}

float TES::dTes(float Tes, float Pj, float Po)
{
    float G=115*pow(10,-12);
    float K=G/(3*pow(Tes,2));
    float C=0.8*pow(10,-12);
    float Tbath=0.055;
    return (Po+Pj-K*(pow(Tes,3)-pow(Tbath,3)))/C;
}

float TES::dI(float I, float V, float R)
{
    float L=121*pow(10,-9);
    float Rl=60*pow(10,-6);
    return (V-I*Rl-I*R)/L;
}


float TES::RK4(ptrf f, float dt, float y0, float y1, float y2)
{
    float k1,k2,k3,k4;
    k1=f(y0,y1,y2);
    k2=f(y0+dt/2*k1,y1,y2);
    k3=f(y0+dt/2*k2,y1,y2);
    k4=f(y0+dt*k3,y1,y2);
    return y0+dt/6*(k1+2*k2+2*k3+k4);
}

float TES::computeLCTES(float dt)
{
    Pj=pow(51.5*pow(10,-9),2)/R;
    I=RK4((Pixel::dI),dt,I,V,R);
    Tes=RK4(Pixel::dTes,dt,Tes,Pj,Po);
    R=R0+alpha*R0/T0*(Tes-T0)+beta*R0/I0*(I-I0);
    //biasm(k)=(-(2-8*C*fe^2)*biasm(k-1)-(1-2*fe*B+4*fe^2*C)*biasm(k-2)+2*fe*A*(bias(k)-bias(k-2)))/(2*fe*B+1+4*C*fe^2);
}

