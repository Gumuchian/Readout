#include "Pixel.h"
#include "BBFB.h"
#include "TES.h"
#include <math.h>

typedef float (*ptrf)(float,float,float);

Pixel::Pixel(){

}

Pixel::Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain, int fe, int N): frequence(frequence),phase_initiale(phase_initiale),phase_retard(phase_retard),amplitude(amplitude),bbfb(gain),compteur(0)
{
    pas=round(N*frequence/fe);
}

int Pixel::getfeedback()
{
    return bbfb.getfeedback();
}

int Pixel::getmodule()
{
    return bbfb.module();
}

float Pixel::computeLC()
{
    return tes.computeLCTES(20000000);
}

void Pixel::computeBBFB(int demoduI, int remoduI, int demoduQ, int remoduQ, int input)
{
    bbfb.compute_feedback(demoduI,remoduI,demoduQ,remoduQ,input);
    compteur=compteur+pas;
}

int Pixel::getcount()
{
    return compteur;
}

void Pixel::setinput_adc(float input)
{
    input_adc=input*pow(2,12);
}

void Pixel::setinputLC(float input)
{
    input_LC=input;
}
