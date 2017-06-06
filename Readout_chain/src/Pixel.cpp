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

void Pixel::computePixel()
{
    tes.computeLCTES(1);
    bbfb.compute_feedback(1,1,1);
    compteur=compteur+pas;
}

int Pixel::getcount()
{
    return compteur;
}
