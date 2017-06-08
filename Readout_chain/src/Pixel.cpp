#include "Pixel.h"
#include "BBFB.h"
#include "TES.h"
#include <math.h>

Pixel::Pixel(){

}

Pixel::Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain, int fe, int N, int retard): frequence(frequence),phase_initiale(phase_initiale),phase_retard(phase_retard),amplitude(amplitude),retard(retard),bbfb(gain)
{
    comptR_I=0;
    comptR_Q=N/4;
    comptD_I=N-((N*retard)*frequence/fe)%N;
    comptD_Q=(comptD_I+N/4)%N;
    pas=(N*frequence)/fe;
    feedback=new int[retard+1];
    int i;
    for (i=0;i<retard;i++){
        feedback[i]=0;
    }
}

int Pixel::getfeedback()
{
    return feedback[retard-1];
}

int Pixel::getmodule()
{
    return bbfb.module();
}

double Pixel::computeLC()
{
    return tes.computeLCTES(20000000);
}

void Pixel::computeBBFB(int demoduI, int remoduI, int demoduQ, int remoduQ, int input, int N)
{
    bbfb.compute_feedback(demoduI,remoduI,demoduQ,remoduQ,input);
    comptR_I=(comptR_I+pas)%N;
    comptD_I=(comptD_I+pas)%N;
    comptR_Q=(comptR_Q+pas)%N;
    comptD_Q=(comptD_Q+pas)%N;
    int i;
    for (i=retard-1;i>0;i--){
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

void Pixel::setPo(double P)
{
    tes.setPo(P);
}

