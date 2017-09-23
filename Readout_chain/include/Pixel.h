#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"
#include "TES.h"

class Pixel
{
    public:
        Pixel();
        Pixel(double frequence, double frequence_ideale, int phase_initiale);
        double getfeedback();
        double getmodule();
        void setinputLC(double input);
        double computeLC();
        void computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input);
        int getcomptR_I();
        int getcomptR_Q();
        int getcomptD_I();
        int getcomptD_Q();
        double getbiasm();
        //void setPo(double P);
        void setI(double p);
        //int getretard();

    protected:

    private:
        double frequence;
        double frequence_ideale;
        int phase_initiale;
        BBFB bbfb;
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
