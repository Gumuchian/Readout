#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"
#include "TES.h"

class Pixel
{
    public:
        Pixel();
        Pixel(double frequence, int phase_initiale, int phase_retard, int amplitude, int gain, double fe, int N, int retard);
        double getfeedback();
        double getmodule();
        void setinputLC(double input);
        double computeLC();
        void computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input, int N);
        int getcomptR_I();
        int getcomptR_Q();
        int getcomptD_I();
        int getcomptD_Q();
        double getbiasm();
        void setPo(double P);
        void setI(double p);
        int getretard();

    protected:

    private:
        double frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        BBFB bbfb;
        double fe;
        int retard;
        int comptD_I;
        int comptR_I;
        int comptD_Q;
        int comptR_Q;
        int pas;
        double *feedback;
        double I;
        double input_adc;
        TES tes;
};

#endif // PIXEL_H
