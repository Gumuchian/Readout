#include "CIC.h"
#include <math.h>
#include <ressources.h>


CIC::CIC()
{
    int i;
    index = 0;
    access = false;
    integ = new double*[order+1];
    comb = new double*[order+1];
    for (i=0;i<order+1;i++)
    {
        integ[i]=new double[2];
        comb[i]=new double[2];
        comb[i][0]=0;comb[i][1]=0;
        integ[i][0]=0;integ[i][1]=0;
    }
}


double CIC::compute(double input)
{
    int i;
    integ[0][1]=input;
    for (i=1;i<order+1;i++)
    {
        integ[i][1]=integ[i][0]+integ[i-1][1];
    }
    if (index==0)
    {
        comb[0][1]=integ[order][1];
        for (i=1;i<order+1;i++)
        {
            comb[i][1]=comb[i-1][1]-comb[i-1][0];
        }
        for (i=0;i<order+1;i++)
        {
            comb[i][0]=comb[i][1];
        }
        access = true;
    }
    else {access = false;}
    for (i=0;i<order+1;i++)
    {
        integ[i][0]=integ[i][1];
    }
    index++;
    index=index%decimation;
    return comb[order][1]/pow(decimation,order);
}

bool CIC::getaccess()
{
    return access;
}
