#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"

class Pixel
{
    public:
        Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude,int gain);

    protected:

    private:
        int frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        BBFB bbfb();
};

#endif // PIXEL_H
