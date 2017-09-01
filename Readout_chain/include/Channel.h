#ifndef CHANNEL_H
#define CHANNEL_H
#include <vector>
#include "Pixel.h"
#include "DDS.h"

class Channel
{
    public:
        Channel();
        Channel(int N, int taille, int precision, int interp, int retard);
        double sumPolar();
        void computeLC_TES(double noise);
        void computeBBFB();
        double getinput();
        double getfck();
        double getmod();
        void setPo(double P);
        void setI(double p);
    protected:
    private:
        int N;
        std::vector<Pixel> ch;
        DDS dds;
        double input;
        double fck;
};

#endif // CHANNEL_H
