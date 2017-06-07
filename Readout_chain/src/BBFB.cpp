#include "BBFB.h"
#include <math.h>

BBFB::BBFB()
{

}

BBFB::BBFB(int gain):I(0),Q(0),feedback(0),gain(gain)
{

}

void BBFB::compute_feedback(int demoduI, int remoduI, int demoduQ, int remoduQ, int input)
{
    I+=(gain*demoduI*input)>>(17+7);
    Q+=(gain*demoduQ*input)>>(17+7);
    feedback = ((remoduI*I)>>20)+((remoduQ*Q)>>20);
}

int BBFB::getfeedback()
{
    return feedback;
}

int BBFB::module()
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
