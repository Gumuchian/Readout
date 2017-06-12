#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"
#include "TES.h"

class Pixel
{
    public:
        Pixel();
        Pixel(int frequence, int phase_initiale, int phase_retard, int amplitude, int gain, int fe, int N, int retard);
        double getfeedback();
        double getmodule();
        int getfrequency();
        void setinputLC(double input);
        double computeLC();
        void computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input, int N);
        int getcomptR_I();
        int getcomptR_Q();
        int getcomptD_I();
        int getcomptD_Q();
        double getbiasm();
        void setPo(double P);
        int getretard();

    protected:

    private:
        int frequence;
        int fe;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        int comptD_I;
        int comptR_I;
        int comptD_Q;
        int comptR_Q;
        int pas;
        double *feedback;
        int retard;
        double input_adc;
        BBFB bbfb;
        TES tes;
};

#endif // PIXEL_H
