#include "BBFB.h"
#include <math.h>

BBFB::BBFB()
{

}

BBFB::BBFB(double gain):I(0),Q(0),feedback(0),gain(gain)
{

}

void BBFB::compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    // Integrateur sur I et Q, /pow(2,17+13) troncature de (17+13) bits cf. codes VHDL: Integrator.vhd: ligne 74 et Real_mult_Complex.vhd :ligne 63-64
    I+=trunc((gain*demoduI*input)/pow(2,17+13));
    Q+=trunc((gain*demoduQ*input)/pow(2,17+13));
    // pow(2,20) troncation de 20 bits cf. Complex_mult_Real: ligne 67
    feedback = trunc(remoduI*I/pow(2,20))+trunc(remoduQ*Q/pow(2,20));
}

double BBFB::getfeedback()
{
    return feedback;
}

double BBFB::module()
{
    /*int i,sigma;
    int u0[2]={I,Q};
    int u1[2];
    if (u0[0]*u1[0]<0){
        sigma = 1;
    }
    else{
        sigma = -1;
    }
    for (i=0;i<10;i++){
        u1[0] = u0[0] - ((sigma*u0[1])>>i);
        u1[1] = u0[1] + ((sigma*u0[0])>>i);
        if (u0[0]*u1[0]<0){
            sigma *=-1;
        }
        u0[0]=u1[0];
        u0[1]=u1[1];
    }*/
    //return 0.60725*u1[1];
    return sqrt(pow(I,2)+pow(Q,2));
}
