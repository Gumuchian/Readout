#ifndef BBFB_H
#define BBFB_H


class BBFB
{
    public:
        BBFB();
        BBFB(double gain);
        void compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input);
        double getfeedback();
        int module();

    protected:

    private:
        double gain;
        double I;
        double Q;
        double feedback;
};

#endif // BBFB_H
