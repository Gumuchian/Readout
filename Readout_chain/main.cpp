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
    double dsl=0.1*pow(10,-12);//pow(10,-130/10);
    double B=600;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> bbg(0.0,dsl*sqrt(B));
    int i,ip=0,j=0,k,l=0,d=128;
    vector<double> module(140000/d,0);
    vector<double> E;
    string str;
    char* ptr;
    double bbfi[2],bbfo[2],sum,Em=0,var=0,TR=4.08,Gb=37000,P=0,maxi;
    bbfo[0]=0;
    bbfi[0]=0;
    double pulse[140000];
    double pattern[140000/d];
    ofstream fichier("test.txt", ios::out);
    ifstream fichier1("Pulse.txt", ios::out);
    //ifstream fichier2("Cov.txt", ios::out);
    if(fichier1)
    {
        for (i=0;i<140000;i++){
            getline(fichier1,str);
            pulse[i]=strtod(str.c_str(),&ptr);
        }
        maxi=pulse[0];
    }
    for (i=0;i<(140000/d);i++)
    {
        pattern[i]=pulse[0]-pulse[(140000/d-1)*d-i*d];
        P=P+pow(pattern[i],2);
        fichier << pattern[i] << endl;
    }
    fichier1.close();
    if(fichier)
    {
        for (i=0;i<1000000;i++)
        {
            bbfi[1]=bbg(gen);
            bbfo[1]=(bbfi[1]+bbfi[0]+(20.0*pow(10,6)/(PI*1000.0)-1)*bbfo[0])/(20.0*pow(10,6)/(PI*1000.0)+1);
            bbfi[0]=bbfi[1];
            bbfo[0]=bbfo[1];

            // sumPolar = somme des bias de chaque pixel
            ch0.sumPolar();
            // compute LC_TES = sortie du LC-TES
            ch0.setI(pulse[ip]+bbfo[1]);
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
                    for (k=0;k<(140000/d);k++)
                    {
                        sum=((maxi-module[140000/d-1-k])*0.5*0.01/pow(2,15)*Gb/pow(2,19)*0.1*TR/sqrt(2)/4)*pattern[k]+sum;
                    }
                    E.push_back(12000*sum/P);

                }
                l++;
                l=l%(140000/d);
            }
            j++;
            j=j%d;
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
        cout << Em << endl << sqrt(var/(E.size()-3)) << endl;
    }
    return 0;
}
