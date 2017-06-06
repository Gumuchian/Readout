#ifndef TES_H
#define TES_H


class TES
{
    public:
        TES();
        float dTes(float Tes, float Pj, float Po);
        float dI(float I, float V, float R);
        float RK4(float (*ptr)(float,float,float), float dt, float y0, float y1, float y2);
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
};

#endif // TES_H
