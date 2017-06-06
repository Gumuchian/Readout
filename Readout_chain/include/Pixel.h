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
        static float dTes(float Tes, float Pj, float Po);
        static float dI(float I, float V, float R);
        float RK4(float (*ptr)(float,float,float), float dt, float y0, float y1, float y2);
        float computeLCTES(float dt);

    protected:

    private:
        int frequence;
        int phase_initiale;
        int phase_retard;
        int amplitude;
        float Tes;
        float Pj;
        float Po;
        float R;
        float I;
        float V;
        float R0;
        float T0;
        float I0;
        float alpha;
        float beta;
        BBFB bbfb;
};

#endif // PIXEL_H
