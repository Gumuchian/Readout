#include <iostream>
#include <math.h>
#include <Channel.h>
#include <fstream>
#include <string>
#include <Pixel.h>

using namespace std;

int main()
{
    /*Channel ch0(pow(2,9),pow(2,18),pow(2,1));
    int i;
    for (i=0;i<100;i++){
        ch0.sumPolar();
        ch0.computeLC_TES();
        ch0.computeBBFB();
    }*/
    Pixel pix(1000000,0,0,1,20,20000000,1000000);
    int i;
    double dac,Gf=10000,LC,fbck;
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
            pix.setinputLC(pow(2,18)*cos(2*M_PI*1.0/20.0*i));
            LC=pix.computeLC();
            fbck=0.5*0.01/pow(2,15)*Gf*((pix.getfeedback())>>5);
            dac=0.5*80*0.0017/(5.8*pow(10,-6))*(LC-0.1*fbck);
            pix.computeBBFB(trunc(pow(2,18)*cos(2*M_PI*1.0/20.0*i)),trunc(pow(2,18)*cos(2*M_PI*1.0/20.0*i)),trunc(pow(2,18)*sin(2*M_PI*1.0/20.0*i)),trunc(pow(2,18)*sin(2*M_PI*1.0/20.0*i)),trunc(pow(2,12)*dac));
            fichier << dac << endl;
        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    return 0;
}
