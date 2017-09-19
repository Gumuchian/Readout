#ifndef TES_H
#define TES_H
#include <random>

typedef double (*ptrm) (double,double,double);


class TES
{
    public:
        TES();
        /*static double dTes(double Tes, double Pj, double Po);
        static double dI(double I, double V, double R);
        double RK4(ptrm f, double dt, double y0, double y1, double y2);*/
        double computeLCTES(double freq, double fe, int precision);
        void setbias(double biass);
        double getI();
        double getbiasm();
        //void setPo(double P);
        void setI(double p);
    protected:

    private:
        /*double Tes;
        double Pj;
        double Po;
        double R;
        double V;
        double T0;
        double alpha;
        double beta;*/
        double I0;
        double R0;
        double I;
        double biasm[3];
        double bias[3];
        double bbfi[2];
        double bbfo[2];
        double dsl;
        double B;
        std::mt19937 gen;
};

#endif // TES_H
