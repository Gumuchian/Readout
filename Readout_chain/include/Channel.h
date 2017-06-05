#ifndef CHANNEL_H
#define CHANNEL_H
#include <vector>
#include "Pixel.h"

class Channel
{
    public:
        Channel();
    protected:
    private:
        std::vector<Pixel> ch;
};

#endif // CHANNEL_H
