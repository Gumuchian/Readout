#ifndef CIC_H
#define CIC_H


class CIC
{
    public:
        CIC();
        double integrateur(double x0, double y0);
        double accumulateur(double x0, double x1);
        double compute(double input);
        bool getaccess();

    private:
        int ordre;
        int f_decimation;
        int indice;
        double **integ;
        double **acc;
        bool access;
        double trunc[3][2];
};

#endif // CIC_H
