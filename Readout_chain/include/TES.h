#ifndef TES_H
#define TES_H

typedef float (*ptrm) (float,float,float);


class TES
{
    public:
        TES();
        static float dTes(float Tes, float Pj, float Po);
        static float dI(float I, float V, float R);
        float RK4(ptrm f, float dt, float y0, float y1, float y2);
        float computeLCTES(float dt);
    protected:

    private:
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
        float biasm[3];
};

#endif // TES_H
