#include "option.h"
#include <cmath>
#include <iostream>

using namespace std;

float Option::d1()
{
    return (log(S0 / K) + (r - Q + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
}

float Option::d2()
{
    return d1() - sigma * sqrt(T);
}

float Option::C()
{
    return S0 * exp(-Q * T) * sncdf.cdf(d1()) - KPV() * sncdf.cdf(d2());
}

float Option::P()
{
    return -S0 * exp(-Q * T) * sncdf.cdf(-d1()) + KPV() * sncdf.cdf(-d2());
}

float Option::KPV()
{
    return K * exp(-r * T);
}

Option::Option(float s0, float k, float t, float rr, float sma, float q)
{
    S0 = s0;
    K = k;
    r = rr;
    sigma = sma;
    T = t;
    Q = q;
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
    return np(d1()) / (S0 * sigma * sqrt(T));
}

float Option::thetaP(bool trading_days)
{
    return thetaC(trading_days) + r * K * exp(-r * T);
}

float Option::thetaC(bool trading_days)
{
    float theta = -(S0 * np(d1()) * sigma / (2 * sqrt(T))) - r * K * exp(-r * T) * sncdf.cdf(d2());

    if (trading_days)
    {
        return theta / 252;
    }
    return theta / 365;
}

float Option::vega()
{
    return S0 * sqrt(T) * np(d1());
}

float Option::rhoC()
{
    return K * T * exp(-r * T) * sncdf.cdf(d2());
}

float Option::rhoP()
{
    return K * T * exp(-r * T) * sncdf.cdf(-d2());
}

void Option::setIV(float sma)
{
    sigma = sma;
}

float Option::diffPriceC(float p, float s)
{
    setIV(s);
    return p - C();
}

float Option::bisection(float p, float s1, float s2)
{
    if (diffPriceC(p, s1) * diffPriceC(p, s2) >= 0)
    {
        cout << "You have not assumed right a and b\n";
        return 0;
    }

    float sm = s1;
    while ((s2 - s1) >= 0.001)
    {
        // Find middle point
        sm = (s2 + s1) / 2;

        // Check if middle point is root
        if (diffPriceC(p, sm) == 0.0)
            break;

        // Decide the side to repeat the steps
        else if (diffPriceC(p, sm) * diffPriceC(p, s1) < 0)
            s2 = sm;
        else
            s1 = sm;
    }
    return sm;
}

float Option::regulaFalsi(float p, float s1, float s2)
{
    if (diffPriceC(p, s1) * diffPriceC(p, s2) >= 0)
    {
        cout << "You have not assumed right a and b\n";
        return 0;
    }

    float sm = s1;

    for (int i = 0; i < 1000; i++)
    {
        // Find the point that touches x axis
        sm = (s1 * diffPriceC(p, s2) - s2 * diffPriceC(p, s1)) / (diffPriceC(p, s2) - diffPriceC(p, s1));

        // Check if the above found point is root
        if (diffPriceC(p, sm) == 0)
            break;

        // Decide the side to repeat the steps
        else if (diffPriceC(p, sm) * diffPriceC(p, sm) < 0)
            s2 = sm;
        else
            s1 = sm;
    }
    return sm;
}