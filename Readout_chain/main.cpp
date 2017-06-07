#include <iostream>
#include <math.h>
#include <Channel.h>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    Channel ch0(pow(2,9),pow(2,18),pow(2,1));
    /*int i;
    for (i=0;i<100;i++){
        ch0.sumPolar();
        ch0.computeLC_TES();
        ch0.computeBBFB();
    }*/
    TES tes;
    int i;
    ofstream fichier("test.txt", ios::out);
    if(fichier)
    {
        for (i=0;i<1000000;i++){
            tes.setbias(cos(2*M_PI*1.0/20.0*i));
            if (i==500000){
                tes.setPo(pow(10,-10));
            }
            else{
                tes.setPo(pow(10,-15));
            }
            fichier << tes.computeLCTES(20000000) << endl;
        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    return 0;
}
