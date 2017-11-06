#include "BBFB.h"
#include <math.h>
#include "ressources.h"

BBFB::BBFB()
{
    I=0;
    Q=0;
    feedback=0;
}

void BBFB::compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    I+=G*trunc(demoduI*input/Npr);
    Q+=G*trunc(demoduQ*input/Npr);
    feedback = pow(2,DAC_bit-ADC_bit)*trunc((remoduI*I+remoduQ*Q)/Npr);
}

double BBFB::getfeedback()
{
    return feedback;
}

double BBFB::module()
{
    return trunc(sqrt(pow(I,2)+pow(Q,2)));
}
