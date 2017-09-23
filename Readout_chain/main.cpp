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

using namespace std;

int main()
{
    Channel ch0;
    CIC cic;
    int i,k,m,ip=0,j=0,l=0;
    vector<double> module(Np/decimation,0);
    vector<double> E;
    vector<double> tab(trunc(2*prctg*Np/decimation),0);
    string str;
    char* ptr;
    double sum,Em=0,var=0,P=0,maxi,max_tab,a;
    double pulse[Np];
    double pattern[Np/decimation];
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
    for (i=0;i<(Np/decimation);i++)
    {
        pattern[i]=pulse[0]-pulse[(Np/decimation-1)*decimation-i*decimation];
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
            ch0.setI(pulse[0]-energie/12000.0*(pulse[0]-pulse[ip]));
            // compute LC_TES = sortie du LC-T ES
            ch0.computeLC_TES();
            // compute le feedback
            ch0.computeBBFB();

            if (i==Np)
            {
                maxi=ch0.getmod();
            }

            a=cic.compute(ch0.getmod()-maxi);
            if (cic.getaccess() && i>(int)(Np*(1-prctg)))
            {
                module.push_back(-a);
                module.erase(module.begin());
                if (l<trunc(2*prctg*Np/decimation))
                {
                    sum=0;
                    for (k=0;k<(Np/decimation);k++)
                    {
                        sum=(module[Np/decimation-1-k]*G_filtre*PE/pow(2,DAC_bit)*Gb/Npr*0.1*TR/sqrt(2))*pattern[k]+sum;
                    }
                    tab[l]=sum;
                }
                if(l==trunc(2*prctg*Np/decimation))
                {
                    max_tab=0;
                    for (m=0;m<(int)tab.size();m++)
                    {
                        if (tab[m]>max_tab)
                        {
                            max_tab=tab[m];
                        }
                    }
                    E.push_back(12000*max_tab/(P*1.217376343));
                }
                l++;
                l=l%(Np/decimation);
            }
            j++;
            j=j%decimation;
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
        cout << "Energie inject\202e: " << energie << " eV" << endl << "Energie moyenne estim\202e: " << Em << " eV" << endl << "Erreur relative: " << abs(energie-Em)/energie << endl;
        cout << "R\202solution: " << sqrt(var/(E.size()-3)) << " eV" << endl;
    }
    return 0;
}
