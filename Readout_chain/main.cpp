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
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace boost::numeric;

typedef complex<double> Complex;
typedef valarray<Complex> CArray;


template<class T>
bool InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse)
{
	typedef ublas::permutation_matrix<std::size_t> pmatrix;
	ublas::matrix<T> A(input);
	pmatrix pm(A.size1());
	int res = lu_factorize(A, pm);
	if (res != 0)
		return false;
	inverse.assign(ublas::identity_matrix<T> (A.size1()));
	lu_substitute(A, pm, inverse);
	return true;
}


void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    CArray even = x[slice(0,N/2,2)];
    CArray  odd = x[slice(1,N/2,2)];

    fft(even);
    fft(odd);

    for (size_t k=0;k<N/2;++k)
    {
        Complex t = polar(1.0,-2*PI*k/N)*odd[k];
        x[k]=even[k]+t;
        x[k+N/2]=even[k]-t;
    }
}

void ifft(CArray& x)
{
    x = x.apply(conj);
    fft(x);
    x = x.apply(conj);
    x /= x.size();
}

double gradient_descent(ublas::vector<double> coeff)
{
    double pas=Nfit/2;
    double x[2]={-3,0};
    ublas::vector<double> X0(order_fit+1),X1(order_fit+1);
    for (int i=0;i<20;i++)
    {
        x[1]=x[0]+pas;
        for (int j=0;j<order_fit+1;j++)
        {
            X0(j)=pow(x[0],order_fit-j);
            X1(j)=pow(x[1],order_fit-j);
        }
        pas/= (ublas::inner_prod(X1,coeff)<ublas::inner_prod(X0,coeff) ? -2:2);
        x[0]=x[1];
    }
    return (double) ublas::inner_prod(X1,coeff);
}

int main()
{
    int mode;
    Channel ch0;
    //CIC cic;
    Butterworth Butter;
    Pulse_generator pulse_generator;
    int i,k,ip=0,l=0,n_alea=0,m;
    vector<double> module(Npat,0);
    vector<double> E;
    string str;
    double sum,Em=0,var=0,P=0,maxi,a=0,energy_mode,puls;
    double *pulse = new double[Npul];
    double *puls_inter = new double[Npat];
    double pattern[8192];
    ublas::matrix<double> X(Nfit,order_fit+1),Z(order_fit+1,order_fit+1);
    for (i=0;i<Nfit;i++)
    {
        for (int j=0;j<order_fit+1;j++)
        {
            X(i,j)=pow(i-Nfit/2,order_fit-j);
        }
    }
    ublas::vector<double> Y(Nfit),poly_max(order_fit+1);
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
        if (i>Np-Nfit*decimation/2)
        //if (i>Np)
        {
            //a=cic.compute(maxi-ch0.getmod());
            a=Butter.compute(maxi-ch0.getmod());
            //if (cic.getaccess())
            if(Butter.getaccess())
            {
                module.push_back(a);
                module.erase(module.begin());
                if (l<Nfit)
                {
                    sum=0;
                    for (k=0;k<Npat;k++)
                    {
                        sum=module[k]*pattern[k]+sum;
                    }
                    Y(l)=sum;
                }
                if (l==Nfit)
                {
                    n_alea=rand()%64;
                    InvertMatrix(ublas::matrix<double> (ublas::prod(ublas::trans(X),X)),Z);
                    poly_max=ublas::prod(ublas::prod(Z,ublas::trans(X)),Y);
                    E.push_back(1000.0*gradient_descent(poly_max)/P);
                }
                /*if (l==0)
                {
                    n_alea=rand()%64;
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
                }*/
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
