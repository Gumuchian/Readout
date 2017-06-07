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
        void setinputLC(double input);
        double computeLC();
        void computeBBFB(int demoduI, int remoduI, int demoduQ, int remoduQ, int input, int N);
        int getcount();
        double getbiasm();
        void setPo(double P);

    protected:

    private:
        int frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        int compteur;
        int pas;
        double input_adc;
        BBFB bbfb;
        TES tes;
};

#endif // PIXEL_H
