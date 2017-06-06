#include "Pixel.h"
#include "BBFB.h"
#include <math.h>

typedef float (*ptrf)(float,float,float);

Pixel::Pixel(){

}

Pixel::Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain): frequence(frequence),phase_initiale(phase_initiale),phase_retard(phase_retard),amplitude(amplitude),bbfb(gain)
{

}

int Pixel::getfeedback()
{
    return bbfb.getfeedback();
}

int Pixel::getmodule()
{
    return bbfb.module();
}



