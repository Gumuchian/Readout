#include "CIC.h"
#include <math.h>

CIC::CIC()
{
    int i;
    f_decimation = 128;
    indice = 0;
    ordre = 2;
    access = false;
    integ = new double*[ordre+1];
    acc = new double*[ordre+1];
    for (i=0;i<ordre+1;i++)
    {
        integ[i]=new double[2];
        acc[i]=new double[2];
        acc[i][0]=0;acc[i][1]=0;
        integ[i][0]=0;integ[i][1]=0;
    }
}


double CIC::compute(double input)
{
    int i;
    integ[0][1]=input;
    for (i=1;i<ordre+1;i++)
    {
        integ[i][1]=integrateur(integ[i][0],integ[i-1][1]/f_decimation);
    }
    if (indice==0)
    {
        acc[0][1]=integ[ordre][1];
        for (i=1;i<ordre+1;i++)
        {
            acc[i][1]=accumulateur(acc[i-1][0],acc[i-1][1]);
        }
        for (i=0;i<ordre+1;i++)
        {
            acc[i][0]=acc[i][1];
        }
        access = true;
    }
    else {access = false;}
    for (i=0;i<ordre+1;i++)
    {
        integ[i][0]=integ[i][1];
    }
    indice++;
    indice=indice%f_decimation;
    return acc[ordre][1];
}

double CIC::integrateur(double x0, double y0)
{
    return x0+y0;
}

double CIC::accumulateur(double x0, double x1)
{
    return x1-x0;
}

bool CIC::getaccess()
{
    return access;
}
