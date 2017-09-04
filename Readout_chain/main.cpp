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
#define PI 3.1415926535

using namespace std;

int main()
{
    Channel ch0(1,pow(2,9),pow(2,18),pow(2,7),0);
    int i,ip=0,j=0,k,l=0,decim=16;
    vector<double> module(140000/decim,0);
    vector<double> E;
    string str;
    char* ptr;
    double sum,Em=0,var=0,TR=4.08,Gb=37000,P=0,maxi;
    double pulse[140000];
    double pattern[140000/decim];
    ofstream fichier("test.txt", ios::out);
    ifstream fichier1("Pulse.txt", ios::out);
    if(fichier1)
    {
        for (i=0;i<140000;i++){
            getline(fichier1,str);
            pulse[i]=strtod(str.c_str(),&ptr);
        }
        maxi=pulse[0];
    }
    for (i=0;i<(140000/decim);i++)
    {
        pattern[i]=pulse[0]-pulse[(140000/decim-1)*decim-i*decim];
        P=P+pow(pattern[i],2);
    }
    fichier1.close();
    if(fichier)
    {
        for (i=0;i<20000000;i++)
        {
            // sumPolar = somme des bias de chaque pixel
            ch0.sumPolar();
            // compute LC_TES = sortie du LC-TES
            ch0.setI(pulse[ip]);
            ch0.computeLC_TES();
            // compute le feedback
            ch0.computeBBFB();
            // sauvegarde les données
            //fichier <<a<<";"<< ch0.getinput()<<";"<<ch0.getfck()<<";"<<ch0.getmod()<< endl <<flush;
            if (i==140000)
            {
                maxi=ch0.getmod();
            }
            if (j==0)
            {
                module.push_back(ch0.getmod());
                module.erase(module.begin());
                if (l==0)
                {
                    sum=0;
                    for (k=0;k<(140000/decim);k++)
                    {
                        sum=((maxi-module[140000/decim-1-k])*0.5*0.01/pow(2,15)*Gb/pow(2,19)*0.1*TR/sqrt(2)/4)*pattern[k]+sum;
                    }
                    E.push_back(12000*sum/P);
                }
                l++;
                l=l%(140000/decim);
            }
            j++;
            j=j%decim;
            ip++;
            ip=ip%140000;
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
