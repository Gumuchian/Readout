#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"
#include "TES.h"

class Pixel
{
    public:
        Pixel();
        Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain, int fe, int N, int retard);
        int getfeedback();
        int getmodule();
        int getfrequency();
        void setinputLC(double input);
        double computeLC();
        void computeBBFB(int demoduI, int remoduI, int demoduQ, int remoduQ, int input, int N);
        int getcomptR_I();
        int getcomptR_Q();
        int getcomptD_I();
        int getcomptD_Q();
        double getbiasm();
        void setPo(double P);

    protected:

    private:
        int frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        int comptD_I;
        int comptR_I;
        int comptD_Q;
        int comptR_Q;
        int pas;
        double input_adc;
        BBFB bbfb;
        TES tes;
};

#endif // PIXEL_H
