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
        int indice;
        double **integ;
        double **acc;
        bool access;
};

#endif // CIC_H
