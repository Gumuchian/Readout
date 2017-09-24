#ifndef RESSOURCES_H_INCLUDED
#define RESSOURCES_H_INCLUDED

// paramètres de simulation
const double fe=20000000; // fréquence d'échantillonnage
const int N=2000000; // nombre de pas de la simulation
const int Npix=1; // nombre de pixels
const double prctg=0.2;
const double PI=3.1415926535;

// paramètres DDS
const int Npt=pow(2,9); // nombre de valeur du DDS
const int Npr=pow(2,18); // nombre de bits pour coder une valeur
const int interpolation=pow(2,20-9); // facteur d'interpolation

// paramètres du bruit
const double dsl=5.1*pow(10,-12); // densité spectrale linéaire d'un TES (A/sqrt(Hz)
const double dsla=0.8*pow(10,-9); // densité spectrale linéaire du LNA (V/sqrt(Hz)
const double Btes=1000; // bande de bruit du TES
const double Ba=20000000; // bande de bruit du LNA
const double fc=1000; // frequence de coupure de la bande de bruit du TES

// Pulse fichier texte
const int Np=140000; // nombre de points d'un pulse
const double energie=706; // énergie d'un pulse en eV

// CIC
const int decimation=128; // facteur de décimation
const int ordre=3; // ordre du CIC

// BBFB
const double G=5000; // gain de l'intégrateur
const double Gb=512; // gain du feedback
const static int rtd=0; // retard de boucle (en pas de simulation)

// DAC
const double PE=0.02; // pleine échelle (A)
const int DAC_bit=16; // nombre de bits du DAC

// ADC
const int ADC_bit=12; // nombre de bits de l'ADC

// Filtre
const double G_filtre=0.5; // gain du filtre de reconstruction et de l'anti-aliasing

// LNA
const double G_LNA=80; // gain du LNA

// SQUID
const double G_SQUID=0.0017/(5.8*pow(10,-6)); // transimpédance du SQUID

// Paramètres du LC-TES
const double R0=0.001;
const double I0=51.5*pow(10,-6);
const double TR=4.08;
const double L=2*pow(10,-6);

#endif // RESSOURCES_H_INCLUDED
