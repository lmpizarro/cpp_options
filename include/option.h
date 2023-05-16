
#ifndef OPTION_HH
#define OPTION_HH
#include <iostream>
#include "cdf.h"

using namespace std;

const float ONE_DAY = 1.0 / 365.0;
class Option
{
private:
    float S0, K, r, sigma, T, Q;
    float simTime = 0;
    StandardNormalCDF sncdf;
    float np(float x);
    float KPV();
    float grealT();

public:
    Option(float S0, float K, float T, float r, float sigma, float Q);
    float d1();
    float d2();
    float C();
    float P();
    float deltaC();
    float deltaP();
    float thetaC(bool);
    float thetaP(bool);
    float rhoC();
    float rhoP();
    float vega();
    float gamma();
    void setIV(float);
    float gS0() { return S0; };
    float gK(){return K;};
    float gexT() { return T; }
    float gSigma() { return sigma; }
    float gQ() { return Q; }
    float gR() { return r; }
    float diffPriceC(float, float);
    float diffPriceP(float, float);


    friend ostream &operator<<(std::ostream &os, Option &s);

    void setSimTime(const float);
    float getSimTime() { return simTime; };
};


#endif