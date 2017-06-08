#ifndef CHANNEL_H
#define CHANNEL_H
#include <vector>
#include "Pixel.h"
#include "DDS.h"

class Channel
{
    public:
        Channel();
        Channel(int taille, int precision, int interp, int retard);
        void sumPolar();
        void computeLC_TES();
        void computeBBFB();
        double getinput();
        double getfck();
    protected:
    private:
        std::vector<Pixel> ch;
        DDS dds;
        double input;
        double fck;
};

#endif // CHANNEL_H
