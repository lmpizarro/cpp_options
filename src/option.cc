#include <cmath>
#include <iostream>
#include "option.h"

BSM::BSM(float s0, float k, float t, float rr, float sma, float q)
{
    S0 = s0;
    K = k;
    r = rr;
    sigma = sma;
    T = t;
    Q = q;
}

float BSM::grealT() const
{
    if (simTime < T)
    {
        return T - simTime;
    }
    return 0;
};

void BSM::setSimTime(const float t)
{
    simTime = t;
};

float BSM::d1() const
{
    float T = grealT();
    return (log(S0 / K) + (r - Q + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
}

float BSM::d2() const
{
    float T = grealT();
    return d1() - sigma * sqrt(T);
}

float BSM::C() const
{
    float T = grealT();
    return S0 * exp(-Q * T) * sncdf.cdf(d1()) - KPV() * sncdf.cdf(d2());
}

float BSM::P() const
{
    float T = grealT();
    return -S0 * exp(-Q * T) * sncdf.cdf(-d1()) + KPV() * sncdf.cdf(-d2());
}

float BSM::KPV() const
{
    float T = grealT();
    return K * exp(-r * T);
}

float BSM::deltaC() const
{
    return sncdf.cdf(d1());
}

float BSM::deltaP() const
{
    return deltaC() - 1.0;
}

float BSM::np(float x) const
{
    return exp(pow(x, 2) / 2) / (sqrt(2 * M_PI));
}

float BSM::gamma() const
{
    float T = grealT();
    return np(d1()) / (S0 * sigma * sqrt(T));
}

float BSM::thetaP(bool trading_days) const
{
    float T = grealT();
    return thetaC(trading_days) + r * K * exp(-r * T);
}

float BSM::thetaC(bool trading_days) const
{
    float T = grealT();
    float theta = -(S0 * np(d1()) * sigma / (2 * sqrt(T))) - r * K * exp(-r * T) * sncdf.cdf(d2());

    if (trading_days)
    {
        return theta / 252;
    }
    return theta / 365;
}

float BSM::vega() const
{
    float T = grealT();
    return S0 * sqrt(T) * np(d1());
}

float BSM::rhoC() const
{
    float T = grealT();
    return K * T * exp(-r * T) * sncdf.cdf(d2());
}

float BSM::rhoP() const
{
    float T = grealT();
    return K * T * exp(-r * T) * sncdf.cdf(-d2());
}

void BSM::setIV(float sma)
{
    sigma = sma;
}

float BSM::diffPriceC(float pc, float s)
{
    setIV(s);
    return pc - C();
}

float BSM::diffPriceP(float pp, float s)
{
    setIV(s);
    return pp - P();
}

// std::ostream &operator<<(std::ostream &os, BSM &s)
void BSM::print(std::ostream &os) const
{
    os << getSimTime() << "," << gS0() << ","
       << C() << "," << deltaC() << "," << thetaC(true) << "," << rhoC() << ","
       << P() << "," << deltaP() << "," << thetaP(true) << "," << rhoP() << ","
       << gamma() << "," << vega();
};