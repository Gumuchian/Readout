#ifndef CIC_H
#define CIC_H


class CIC
{
    public:
        CIC();
        double compute(double input);
        bool getaccess();

    private:
        int index;
        double **integ;
        double **comb;
        bool access;
};

#endif // CIC_H
