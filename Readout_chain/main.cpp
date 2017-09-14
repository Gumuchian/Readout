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
#include "CIC.h"
#define PI 3.1415926535

/** Paramètres de simulation **/

#define energie 7850.0
#define Npr pow(2,18)
#define Npt pow(2,9)
#define interpolation pow(2,20-9)
#define retard 0
#define Npix 1
#define Np 140000
#define N 2000000
#define prctg 0.2

/****/

using namespace std;

int main()
{
    Channel ch0(Npix,Npt,Npr,interpolation,retard);
    CIC cic;
    int i,ip=0,j=0,k,l=0,decim=128,m;
    vector<double> module(Np/decim,0);
    vector<double> E;
    vector<double> tab(trunc(2*prctg*Np/decim),0);
    string str;
    char* ptr;
    double sum,Em=0,var=0,TR=4.08,Gb=37000,P=0,maxi,max_tab;
    double pulse[Np];
    double pattern[Np/decim];
    ofstream fichier("test.txt", ios::out);
    ifstream fichier1("Pulse.txt", ios::out);
    if(fichier1)
    {
        for (i=0;i<Np;i++){
            getline(fichier1,str);
            pulse[i]=strtod(str.c_str(),&ptr);
        }
        maxi=pulse[0];
    }
    for (i=0;i<(Np/decim);i++)
    {
        pattern[i]=pulse[0]-pulse[(Np/decim-1)*decim-i*decim];
        P=P+pow(pattern[i],2);
    }
    fichier1.close();
    if(fichier)
    {
        for (i=0;i<N;i++)
        {
            // sumPolar = somme des bias de chaque pixel
            ch0.sumPolar();
            // modulation du bias par pulse
            ch0.setI(energie/12000.0*pulse[ip]);
            // compute LC_TES = sortie du LC-TES
            ch0.computeLC_TES();
            // compute le feedback
            ch0.computeBBFB();
            // sauvegarde les données
            //fichier << a << ";" << ch0.getinput() << ";" << ch0.getfck() << ";" << ch0.getmod() << endl;
            //a=cic.compute(ch0.getmod());
            //fichier << a << endl;
            if (i==Np)
            {
                maxi=ch0.getmod();
            }
            if (j==0 && i>(int)(Np*(1-prctg)))
            {
                module.push_back(ch0.getmod());
                module.erase(module.begin());
                if (l<trunc(2*prctg*Np/decim))
                {
                    sum=0;
                    for (k=0;k<(Np/decim);k++)
                    {
                        sum=((maxi-module[Np/decim-1-k])*0.5*0.02/pow(2,16)*Gb/Npr*0.1*TR/sqrt(2))*pattern[k]+sum;
                    }
                    tab[l]=sum;
                }
                if(l==trunc(2*prctg*Np/decim))
                {
                    max_tab=0;
                    for (m=0;m<(int)tab.size();m++)
                    {
                        if (tab[m]>max_tab)
                        {
                            max_tab=tab[m];
                        }
                    }
                    E.push_back(12000*max_tab/(P*1.2333333));
                }
                l++;
                l=l%(Np/decim);
            }
            j++;
            j=j%decim;
            ip++;
            ip=ip%Np;
        }
        fichier.close();
        for (i=3;i<(int)E.size();i++)
        {
            Em=abs(E[i])+Em;
        }
        Em=Em/(E.size()-3);
        for (i=3;i<(int)E.size();i++)
        {
            var=pow(abs(E[i])-Em,2)+var;
        }
        cout << "Energie moyenne estim\202e: " << Em << " eV" << endl << "R\202solution: " << sqrt(var/(E.size()-3)) << " eV" << endl;
    }
    return 0;
}
