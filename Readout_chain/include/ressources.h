#ifndef RESSOURCES_H_INCLUDED
#define RESSOURCES_H_INCLUDED

// paramètres de simulation
int Np=20000000;
int N_pix=1;

// paramètres DDS
int Npt=pow(2,9);
int Npr=pow(2,18);
int interp=pow(2,7);

// paramètres du bruit
double dsl=0.1*pow(10,-12);
double B=1000;
double Ba=10000000;
double dsla=1.0*pow(10,-9);

// Pulse fichier texte
int N_pulse=140000;

// CIC
int decim =128;

//BBFB
double Gb=37000;

// paramètres du LC-TES
double R0=0.001;
double T0=0.09;
double I0=51.5*pow(10,-6);
double V=51.5*pow(10,-9);
double alpha=75;
double beta=1.25;
double G=115.0*pow(10,-12);
double C=0.8*pow(10,-12);
double Tbath=0.055;
double Rl=60*pow(10,-6);
double L=121*pow(10,-9);
double TR=4.08;

#endif // RESSOURCES_H_INCLUDED
