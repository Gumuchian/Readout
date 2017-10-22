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
    double sum,Em[3],var[3],P[3],maxi,a,En[3];
    double pulse[Npul],puls,sum_I;
    double pattern[8192][3];
    ofstream file1("test.txt", ios::out);
    ifstream file("Pattern.txt", ios::out);

    for (i=0;i<2000000;i++)
    {
        if (i==1000000)
        {
            pulse_generator.setPopt(energy);
        }
        puls=pulse_generator.compute();
        if (i>=1000000 && i<1000000+Npul)
        {
            pulse[ip]=puls;
            ip++;
        }
    }
    ip=0;

    for (i=0;i<8192;i++)
    {
        for (j=0;j<3;j++)
        {
            file >> pattern[i][j];
        }
    }

    P[0]=0;P[1]=0;P[2]=0;
    for (j=0;j<3;j++)
    {
        sum_I=0;
        for (i=0;i<Npat;i++)
        {
            pattern[i][j]=pulse[0]-pattern[i][j];
            P[j]=P[j]+pow(pattern[i][j],2);
            sum_I=sum_I+pattern[i][j];
        }
        En[j]=sum_I*Vp*decimation/(1.6*pow(10,-19)*fs);
    }

    for (i=0;i<N;i++)
    {
        // sumPolar = bias sum of each pixel
        ch0.sumPolar();
        // bias modulation by pulse
        if (ip<Npul)
        {
            ch0.setI(pulse[ip]);
        }
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
                    for (j=0;j<3;j++)
                    {
                        sum=0;
                        for (k=0;k<Npat;k++)
                        {
                            sum=(module[k]*G_filter*PE/pow(2,DAC_bit)*Gb/Npr*0.1*TR/sqrt(2))*pattern[k][j]+sum;
                        }
                        E.push_back(En[j]*sum/P[j]);
                    }
                }
                l++;
                l=l%Npat;
            }
        }
        ip++;
        ip=ip%(Npat*decimation);
    }
    for (j=0;j<3;j++)
    {
        Em[j]=0;
        var[j]=0;
        for (i=3;i<(int)E.size()/3;i++)
        {
            Em[j]=abs(E[i*3+j])+Em[j];
        }
        Em[j]=Em[j]*3/(E.size()-9);

        for (i=3;i<(int)E.size()/3;i++)
        {
            var[j]=pow(abs(E[i*3+j])-Em[j],2)+var[j];
        }
    }
    cout << "Input energy: " << energy << " eV" << endl;
    cout << "Number of estimations: " << (E.size()-9)/3 << endl;
    for (i=0;i<3;i++)
    {
        cout << "E" << i << ":" << endl;
        cout << "\t" << "Energy estimation: " << Em[i] << " eV" << endl;
        cout << "\t" << "Relative error: " << abs(energy-Em[i])/energy << endl;
        cout << "\t" << "Resolution: " << 2.35*sqrt(var[i]*3/(E.size()-9)) << " eV" << endl;
    }
    return 0;
}
