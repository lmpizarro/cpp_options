#include <cmath>
#include <iostream>
#include "option.h"

using namespace std;

Option::Option(Type s0, Type k, Type t, Type rr, Type sma, Type q)
{
    S0 = s0;
    K = k;
    r = rr;
    sigma = sma;
    T = t;
    Q = q;
}

template <class Type> Type Option::grealT(){
    if (simTime < T){
        return T - simTime;
    }
    return 0;
};

void Option::setSimTime(const float t){
    simTime = t;
};

float Option::d1()
{
    float T = grealT();
    return (log(S0 / K) + (r - Q + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
}

float Option::d2()
{
    float T = grealT();
    return d1() - sigma * sqrt(T);
}

float Option::C()
{
    float T = grealT();
    return S0 * exp(-Q * T) * sncdf.cdf(d1()) - KPV() * sncdf.cdf(d2());
}

float Option::P()
{
    float T = grealT();
    return -S0 * exp(-Q * T) * sncdf.cdf(-d1()) + KPV() * sncdf.cdf(-d2());
}

float Option::KPV()
{
    float T = grealT();
    return K * exp(-r * T);
}



float Option::deltaC()
{
    return sncdf.cdf(d1());
}

float Option::deltaP()
{
    return deltaC() - 1.0;
}

float Option::np(float x)
{
    return exp(pow(x, 2) / 2) / (sqrt(2 * M_PI));
}

float Option::gamma()
{
    float T = grealT();
    return np(d1()) / (S0 * sigma * sqrt(T));
}

float Option::thetaP(bool trading_days)
{
    float T = grealT();
    return thetaC(trading_days) + r * K * exp(-r * T);
}

float Option::thetaC(bool trading_days)
{
    float T = grealT();
    float theta = -(S0 * np(d1()) * sigma / (2 * sqrt(T))) - r * K * exp(-r * T) * sncdf.cdf(d2());

    if (trading_days)
    {
        return theta / 252;
    }
    return theta / 365;
}

float Option::vega()
{
    float T = grealT();
    return S0 * sqrt(T) * np(d1());
}

float Option::rhoC()
{
    float T = grealT();
    return K * T * exp(-r * T) * sncdf.cdf(d2());
}

float Option::rhoP()
{
    float T = grealT();
    return K * T * exp(-r * T) * sncdf.cdf(-d2());
}

void Option::setIV(float sma)
{
    sigma = sma;
}

float Option::diffPriceC(float pc, float s)
{
    setIV(s);
    return pc - C();
}

float Option::diffPriceP(float pp, float s)
{
    setIV(s);
    return pp - P();
}


ostream &operator<<(ostream &os, Option &s)
{
    os << s.getSimTime() << "," << s.S0 << ","
       << s.C() << "," << s.deltaC() << "," << s.thetaC(true) << "," << s.rhoC() << ","
       << s.P() << "," << s.deltaP() << "," << s.thetaP(true) << "," << s.rhoP() << ","
       << s.gamma()  << "," << s.vega();
    return os;
};



