#include <iostream>
#include <math.h>
#include <Channel.h>
#include <fstream>
#include <string>
#include <Pixel.h>
#include <Channel.h>

using namespace std;

int main()
{
    Channel ch0(1,pow(2,9),pow(2,18),pow(2,7),0);
    int i;
    ofstream fichier("test.txt", ios::out);
    if(fichier)
    {
        for (i=0;i<1000000;i++)
        {
            if (i==500000){
                ch0.setPo(pow(10,-8));
            }
            else{
                ch0.setPo(0);
            }
            ch0.sumPolar();
            ch0.computeLC_TES();
            ch0.computeBBFB();
            fichier << ch0.getmod() << endl;
        }
    }
    fichier.close();
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
