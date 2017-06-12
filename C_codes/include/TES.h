#ifndef TES_H
#define TES_H

typedef double (*ptrm) (double,double,double);


class TES
{
    public:
        TES();
        static double dTes(double Tes, double Pj, double Po);
        static double dI(double I, double V, double R);
        double RK4(ptrm f, double dt, double y0, double y1, double y2);
        double computeLCTES(double freq,double fe);
        void setbias(double biass);
        double getI();
        double getbiasm();
        void setPo(double P);
    protected:

    private:
        double Tes;
        double Pj;
        double Po;
        double R;
        double I;
        double V;
        double R0;
        double T0;
        double I0;
        double alpha;
        double beta;
        double biasm[3];
        double bias[3];
};

#endif // TES_H
