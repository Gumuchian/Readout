#include <iostream>
#include <math.h>
#include <Channel.h>
#include <fstream>
#include <string>
#include <Pixel.h>
#include <Channel.h>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include "ressources.h"
#include <CIC.h>
#include <DDS.h>
#include <Butterworth.h>
#include <Pulse_generator.h>

using namespace std;

int main()
{
    Channel ch0;
    //CIC cic;
    Butterworth Butter;
    Pulse_generator pulse_generator;
    int i,j,k,m,ip=0,l=0,n=0;
    vector<double> module(Npat,0);
    vector<double> E;
    string str;
    //char* ptr;
    double sum,Em=0,var=0,P=0,maxi,a;
    double pulse[Np],puls;
    double pattern[Npat][3];
    ofstream file1("test.txt", ios::out);
    ifstream file("Pattern.txt", ios::out);

    for (i=0;i<2000000;i++)
    {
        if (i==1000000)
        {
            pulse_generator.setPopt(energy);
        }
        puls=pulse_generator.compute();
        if (i>=1000000 && i<1000000+Np)
        {
            pulse[ip]=puls;
            ip++;
        }
    }
    ip=0;

    for (i=0;i<Np/decimation+1;i++)
    {
        P=P+pow(pattern[i],2);
    }

    for (i=0;i<N;i++)
    {
        // sumPolar = bias sum of each pixel
        ch0.sumPolar();
        // bias modulation by pulse
        ch0.setI(pulse[ip]);
        // compute LC_TES = output of LC-TES
        ch0.computeLC_TES();
        // compute feedback
        ch0.computeBBFB();

        if (i==Np)
        {
            maxi=ch0.getmod();
        }
        if (i>Np)
        {
            //a=cic.compute(maxi-ch0.getmod());
            a=Butter.compute(maxi-ch0.getmod());
            //if (cic.getaccess())
            if(Butter.getaccess())
            {
                module.push_back(a);
                module.erase(module.begin());
                if (l==0)
                {
                    sum=0;
                    for (k=0;k<Np/decimation+1;k++)
                    {
                        sum=(module[Np/decimation-k]*G_filter*PE/pow(2,DAC_bit)*Gb/Npr*0.1*TR/sqrt(2))*pattern[k]+sum;
                    }
                    E.push_back(energy*sum/P);
                    n++;
                    if (n==4){m=1;}else{m=0;}
                    n=n%4;
                }
                l++;
                l=l%(Np/decimation+1-m);
            }
        }
        ip++;
        ip=ip%Np;
    }

    for (i=3;i<(int)E.size();i++)
    {
        Em=abs(E[i])+Em;
    }
    Em=Em/(E.size()-3);

    for (i=3;i<(int)E.size();i++)
    {
        var=pow(abs(E[i])-Em,2)+var;
    }

    cout << "Input energy: " << energy << " eV" << endl << "Energy estimation: " << Em << " eV" << endl << "Relative error: " << abs(energy-Em)/energy << endl;
    cout << "Resolution: " << 2.35*sqrt(var/(E.size()-3)) << " eV" << endl;
    return 0;
}
