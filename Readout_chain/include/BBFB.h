#ifndef BBFB_H
#define BBFB_H


class BBFB
{
    public:
        BBFB();
        BBFB(double gain);
        void compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, int precision, double input);
        double getfeedback();
        double module();

    protected:

    private:
        double I;
        double Q;
        double feedback;
        double gain;
};

#endif // BBFB_H
