#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"

class Pixel
{
    public:
        Pixel();
        Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain);
        int getfeedback();
        int getmodule();


    protected:

    private:
        int frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        BBFB bbfb;
        TES tes;
};

#endif // PIXEL_H
