#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"
#include "TES.h"

class Pixel
{
    public:
        Pixel();
        Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain, int fe, int N);
        int getfeedback();
        int getmodule();
        int getfrequency();
        void setinput_adc(float input);
        void computePixel();
        int getcount();

    protected:

    private:
        int frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        int compteur;
        int pas;
        int input_adc;
        int feedback;
        BBFB bbfb;
        TES tes;
};

#endif // PIXEL_H
