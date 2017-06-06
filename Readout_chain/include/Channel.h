#ifndef CHANNEL_H
#define CHANNEL_H
#include <vector>
#include "Pixel.h"
#include "DDS.h"

class Channel
{
    public:
        Channel();
        Channel(int taille, int precision, int interp);
        void sumPolar();
        void computeLC_TES();
        void computeBBFB();
    protected:
    private:
        std::vector<Pixel> ch;
        DDS dds;
        float input;
};

#endif // CHANNEL_H
