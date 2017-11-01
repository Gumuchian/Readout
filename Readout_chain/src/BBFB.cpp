#include "BBFB.h"
#include <math.h>
#include "ressources.h"

BBFB::BBFB()
{
    I=0;
    Q=0;
    feedback=0;
}

void BBFB::compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    I+=G*trunc(demoduI*input/Npr);
    Q+=G*trunc(demoduQ*input/Npr);
    feedback = trunc((remoduI*I+remoduQ*Q)/Npr);
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
