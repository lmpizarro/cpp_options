
#ifndef OPTION_HH
#define OPTION_HH
#include <iostream>
#include "cdf.h"

using namespace std;

const float ONE_DAY = 1.0 / 365.0;
template <class Type> class Option
{
private:
    Type S0, K, r, sigma, T, Q;
    Type simTime = 0;
    StandardNormalCDF sncdf;
    Type np(float x);
    Type KPV();
    Type grealT();

public:
    Option(Type S0, Type K, Type T, Type r, Type sigma, Type Q);
    Type d1();
    Type d2();
    Type C();
    Type P();
    Type deltaC();
    Type deltaP();
    Type thetaC(bool);
    Type thetaP(bool);
    Type rhoC();
    Type rhoP();
    Type vega();
    Type gamma();
    void setIV(float);
    Type gS0() { return S0; };
    Type gK(){return K;};
    Type gexT() { return T; }
    Type gSigma() { return sigma; }
    Type gQ() { return Q; }
    Type gR() { return r; }
    friend ostream &operator<<(std::ostream &os, Option &s);

    Type diffPriceC(float, float);
    Type diffPriceP(float, float);

    void setSimTime(const float);
    Type getSimTime() { return simTime; };
};


#endif