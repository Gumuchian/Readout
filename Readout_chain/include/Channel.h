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
        float sumPolar();
        float setBias();
        void computeSQUID();
    protected:
    private:
        std::vector<Pixel> ch;
        DDS dds;
};

#endif // CHANNEL_H
