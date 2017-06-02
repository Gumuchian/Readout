#include "Pixel.h"
#include "BBFB.h"

Pixel::Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain)
{
    frequence = frequence;
    phase_initiale = phase_initiale;
    phase_retard = phase_retard;
    amplitude = amplitude;
    bbfb -> BBFB(4);
}
