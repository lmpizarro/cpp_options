
#ifndef OPTION_HH
#define OPTION_HH
#include "cdf.h"

class Option
{
private:
    float S0, K, r, sigma, T, Q;
    StandardNormalCDF sncdf;
    float np(float x);
    float KPV();

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
    float diffPriceC(float, float);
    float bisection(float, float, float);
    float regulaFalsi(float, float, float);
};

#endif