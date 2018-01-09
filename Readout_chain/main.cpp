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
#include <complex>
#include <valarray>

using namespace std;

typedef complex<double> Complex;
typedef valarray<Complex> CArray;

void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    CArray even = x[std::slice(0,N/2,2)];
    CArray  odd = x[std::slice(1,N/2,2)];

    fft(even);
    fft(odd);

    for (size_t k=0;k<N/2;++k)
    {
        Complex t = std::polar(1.0,-2*PI*k/N)*odd[k];
        x[k]=even[k]+t;
        x[k+N/2]=even[k]-t;
    }
}

void ifft(CArray& x)
{
    x = x.apply(std::conj);
    fft(x);
    x = x.apply(std::conj);
    x /= x.size();
}

int main()
{
    int mode;
    Channel ch0;
    //CIC cic;
    Butterworth Butter;
    Pulse_generator pulse_generator;
    int i,k,ip=0,l=0,m,n_alea=0;
    vector<double> module(Npat,0);
    vector<double> E;
    string str;
    double sum,Em=0,var=0,P=0,maxi,a=0,energy_mode;
    double pulse[Npul],puls,puls_inter[Npat];
    double pattern[8192];
    fstream file1,file2,file3;
    file3.open("test.txt",ios::out);
    CArray sig_fft (Npat);
    CArray sig_ph (Npat);
    CArray noise_fft (Npat);
    for (i=0;i<Npat;i++)
    {
        noise_fft[i]=0;
        sig_fft[i]=0;
    }
    CArray div_fft (Npat);
    Complex c[Npat];
    const Complex const_i(0,1);

    cout << "Select mode:" << endl << "\t1: Calibration" << endl << "\t2: Resolution estimation" << endl << "(1 or 2)" << endl;
    cin >> mode;
    cout << "Processing..." << endl;

    if (mode==1)
    {
        file1.open("Pattern.txt",ios::out);
        file2.open("Facteur.txt",ios::out);
        energy_mode=1000;
    }
    else
    {
        file1.open("Pattern.txt",ios::in);
        file2.open("Facteur.txt",ios::in);
        energy_mode=energy;
        file2 >> P;
    }

    for (i=0;i<3000000;i++)
    {
        if (i==1000000)
        {
            pulse_generator.setPopt(energy_mode);
        }
        puls=pulse_generator.compute();
        if (i>=1000000 && i<1000000+Npul)
        {
            pulse[ip]=puls;
            ip++;
        }
    }
    ip=0;

    if (mode==2)
    {
        for (i=0;i<Npat;i++)
        {
            file1 >> pattern[i];
        }
    }

    for (i=0;i<N;i++)
    {
        // sumPolar = bias sum of each pixel
        ch0.sumPolar();
        // bias modulation by pulse
        if (mode==2)
        {
            if (ip<Npul+n_alea)
            {
                if (ip>=n_alea)
                {
                    ch0.setI(pulse[ip-n_alea]);
                }
            }
        }
        else
        {
            if (i<N/2 && ip<Npul)
            {
                ch0.setI(pulse[ip]);
            }
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
                file3 << a << endl;
                module.push_back(a);
                module.erase(module.begin());
                if (l==0)
                {
                    //n_alea=rand()%5;
                    if (mode==1)
                    {
                        for (k=0;k<Npat;k++)
                        {
                            c[k]=module[k];
                        }
                        CArray mod(c,Npat);
                        fft(mod);
                        if (i<N/2)
                        {
                            sig_fft+=abs(mod);
                            for (m=0;m<Npat;m++)
                            {
                                sig_ph[m]=arg(mod[m]);
                                puls_inter[m]=module[m];
                            }
                        }
                        else
                        {
                            noise_fft+=abs(mod);
                        }
                    }
                    else
                    {
                        sum=0;
                        for (k=0;k<Npat;k++)
                        {
                            sum=module[k]*pattern[k]+sum;
                        }
                        E.push_back(1000.0*sum/P);
                    }
                }
                l++;
                l=l%Npat;
            }
        }
        ip++;
        ip=ip%Np;
    }

    if (mode==1)
    {
        div_fft=sig_fft/noise_fft;
        for (i=0;i<Npat;i++)
        {
            div_fft[i]*=exp(const_i*sig_ph[i]);
        }
        ifft(div_fft);
        for (i=0;i<Npat;i++)
        {
            file1 << real(div_fft[i]) << endl;
            P+=puls_inter[i]*real(div_fft[i]);
        }
        file2 << P;
        cout << "done" << endl;
    }
    else
    {
        for (i=3;i<(int)E.size();i++)
        {
            Em=abs(E[i])+Em;
        }
        Em=Em/(E.size()-3);

        for (i=3;i<(int)E.size();i++)
        {
            var=pow(abs(E[i]-Em),2)+var;
        }
        var=2.35*sqrt(var/(E.size()-3));

        cout << "Input energy: " << energy << " eV" << endl;
        cout << "Number of estimations: " << E.size()-3 << endl;
        cout << "E:  pattern @ " << 1000 << " eV" << endl;
        cout << "\tEnergy estimation: " << Em << " eV" << endl;
        cout << "\tRelative error: " << abs(energy-Em)/energy << endl;
        cout << "\tResolution: " << var << " eV" << endl;
    }
    file1.close();
    file2.close();
    file3.close();
    return 0;
}
