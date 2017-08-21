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
#define M_PI 3.1415926535

using namespace std;

int main()
{
    // initialise un channel
    Channel ch0(1,pow(2,9),pow(2,18),pow(2,7),0);
    random_device rd;
    mt19937 gen(rd());
    double dsl=0.1*pow(10,-12);//pow(10,-130/10);
    double B=600;
    normal_distribution<double> b(0.0,dsl*sqrt(B));
    int i,ip=0,j=0,k,l=0;
    vector<double> module(1093,0);
    vector<double> E;
    string str;
    char* ptr;
    double a,bbfi[2],bbfo[2],sum,Em=0,var=0,TR=4.08,Gb=37000;
    bbfo[0]=0;
    bbfi[0]=0;
    double pulse[140000];
    double pattern[1093];
    ofstream fichier("test.txt", ios::out);
    ifstream fichier1("Pulse.txt", ios::out);
    if(fichier1)
    {
        for (i=0;i<140000;i++){
            getline(fichier1,str);
            pulse[i]=strtod(str.c_str(),&ptr);
        }
    }
    for (i=0;i<1093;i++)
    {
        pattern[i]=pulse[(1093-1)*128-i*128];
    }
    fichier1.close();
    if(fichier)
    {
        for (i=0;i<10000000;i++)
        {
            bbfi[1]=b(gen);
            bbfo[1]=(20.0*pow(10,6)/(M_PI*1000.0)+1)*(bbfi[1]+bbfi[0]+(20.0*pow(10,6)/(M_PI*1000.0)-1)*bbfo[0]);
            bbfi[0]=bbfi[1];
            bbfo[0]=bbfo[1];
            // Le if permet de definir a quel indice on reçoit un photon
            /*if (i==500000){
                // On definit la puissance recue en Watt
                ch0.setPo(pow(10,-8));
            }
            else{
                ch0.setPo(0);
            }*/
            // sumPolar = somme des bias de chaque pixel
            a=ch0.sumPolar();
            // compute LC_TES = sortie du LC-TES
            ch0.setI(pulse[ip]);
            ch0.computeLC_TES();
            // compute le feedback
            ch0.computeBBFB();
            // sauvegarde les données
            //fichier <<a<<";"<< ch0.getinput()<<";"<<ch0.getfck()<<";"<<ch0.getmod()<< endl <<flush;
            if (j==0)
            {
                module.push_back(ch0.getmod());
                module.erase(module.begin());
                //fichier <<ch0.getmod()*0.5*0.01/pow(2,15)*Gb/pow(2,19)*0.1*TR/sqrt(2)/4<< endl <<flush;

                if (l==0)
                {
                    sum=0;
                    for (k=0;k<1093;k++)
                    {
                        sum=(pattern[0]-module[1092-k]*0.5*0.01/pow(2,15)*Gb/pow(2,19)*0.1*TR/sqrt(2)/4)*(pattern[0]-pattern[k])+sum;
                    }
                    E.push_back(12000*sum/(1.27035613*pow(10,-5)));
                }
                l++;
                l=l%1093;
            }
            j++;
            j=j%128;
            ip++;
            ip=ip%140000;
        }
        fichier.close();
        for (i=3;i<E.size();i++){
            Em=abs(E[i])+Em;
        }
        Em=Em/(E.size()-3);
        for (i=3;i<E.size();i++){
            var=pow(abs(E[i])-Em,2)+var;
        }
        cout << sqrt(var/(E.size()-3)) << endl;
    }
    /*
    Pixel pix(1000000,0,0,1,4,20000000,pow(2,16),1);
    DDS dds(pow(2,9),pow(2,18),pow(2,7));
    int i,Gf=1000;
    double dac,LC,fbck;
    ofstream fichier("test.txt", ios::out);
    if(fichier)
    {
        for (i=0;i<1000000;i++){
            if (i==500000){
                pix.setPo(pow(10,-8));
            }
            else{
                pix.setPo(0);
            }
            pix.setinputLC(dds.getvalue(pix.getcomptR_I()));
            LC=pix.computeLC();
            fbck=0.5*0.01/pow(2,15)*((Gf*pix.getfeedback())/pow(2,19));
            dac=0.5*80*0.0017/(5.8*pow(10,-6))*(LC-0.1*fbck);
            pix.computeBBFB(dds.getvalue(pix.getcomptD_I()),dds.getvalue(pix.getcomptR_I()),dds.getvalue(pix.getcomptD_Q()),dds.getvalue(pix.getcomptR_Q()),trunc(pow(2,12)*dac),pow(2,16));
            fichier << dac << endl;
        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;*/
    return 0;
}
