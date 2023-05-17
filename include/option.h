
#ifndef OPTION_HH
#define OPTION_HH
#include <iostream>
#include "cdf.h"

using namespace std;

const float ONE_DAY = 1.0 / 365.0;
template <typename Type>
class Option
{
public:
    Type S0, K, r, sigma, T, Q;
    Type simTime = 0;
    Type grealT()const;

    Option(Type S0, Type K, Type T, Type r, Type sigma, Type Q);
    virtual Type C(){ return 0; };
    virtual Type P(){ return 0; };
    virtual Type deltaC(){ return 0; };
    virtual Type deltaP(){ return 0; };
    virtual Type thetaC(bool) { return 0; };
    virtual Type thetaP(bool) { return 0; };
    virtual Type rhoC() { return 0; };
    virtual Type rhoP() { return 0; };
    virtual Type vega() { return 0; };
    virtual Type gamma() { return 0; };
    void setIV(Type);
    Type gS0()const{ return S0; };
    Type gK()const{ return K; };
    Type gexT()const{ return T; }
    Type gSigma()const{ return sigma; }
    Type gQ()const{ return Q; }
    Type gR()const{ return r; }
    friend ostream &operator<<(std::ostream &os, Option &s);

    Type diffPriceC(Type, Type);
    Type diffPriceP(Type, Type);

    void setSimTime(const Type);
    Type getSimTime()const{ return simTime; };
};


#endif