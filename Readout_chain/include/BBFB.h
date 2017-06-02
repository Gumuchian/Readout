#ifndef BBFB_H
#define BBFB_H


class BBFB
{
    public:
        BBFB(int gain);
        void compute_feedback(int c, int s, int input);
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
