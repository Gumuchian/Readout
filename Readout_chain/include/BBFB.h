#ifndef BBFB_H
#define BBFB_H


class BBFB
{
    public:
        BBFB();
        BBFB(int gain);
        void compute_feedback(int demoduI, int remoduI, int demoduQ, int remoduQ, int input);
        int getfeedback();
        int module();

    protected:

    private:
        int gain;
        int I;
        int Q;
        int feedback;
};

#endif // BBFB_H
