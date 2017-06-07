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
    Pixel pix;
    //TES tes;
    int i;
    double dac,Gf=1000;
    ofstream fichier("test.txt", ios::out);
    if(fichier)
    {
        for (i=0;i<100000;i++){
            /*tes.setbias(cos(2*M_PI*1.0/20.0*i));
            if (i==500000){
                tes.setPo(pow(10,-10));
            }
            else{
                tes.setPo(pow(10,-15));
            }
            fichier << tes.computeLCTES(20000000) << endl;*/
            pix.setinputLC(cos(2*M_PI*1.0/20.0*i));
            dac=0.5*80*0.0017/(5.8*pow(10,-6))*(pix.computeLC()-0.5*0.1/pow(2,15)*Gf*((pix.getfeedback())>>19));
            pix.computeBBFB(pow(2,18)*cos(2*M_PI*1.0/20.0*i),pow(2,18)*cos(2*M_PI*1.0/20.0*i),pow(2,18)*sin(2*M_PI*1.0/20.0*i),pow(2,18)*sin(2*M_PI*1.0/20.0*i),round(pow(2,12)*dac));
            fichier << pix.getfeedback() << endl;
        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    return 0;
}
