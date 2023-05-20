#include <cmath>
#include <iostream>
#include "option.h"
#include "bsm.h"

using namespace std;

template <typename T2> BSM<T2>::BSM(T2 s0, T2 k, T2 t, T2 rr, T2 sma, T2 q):Option<T2>(s0,k,t,rr,sma,q)
{
}

template <typename T2> T2 BSM<T2>::d1()
{
    T2 T = grealT();
    T2 sigma = gSigma();
    T2 S0 = gS0();
    T2 K = gK();
    T2 r = gR();
    T2 Q = gQ();
    return (log(S0 / K) + (r - Q + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
}

template <typename T2> T2 BSM<T2>::d2()
{
    T2 T = grealT();
    T2 sigma = gSigma();
    return d1() - sigma * sqrt(T);
}

template <typename T2> T2 BSM<T2>::KPV()
{
    T2 T = grealT();
    T2 r = gR();
    T2 K = gK();
    return K * exp(-r * T);
}


template <typename T2> T2 BSM<T2>::np(T2 x)
{
    return exp(pow(x, 2) / 2) / (sqrt(2 * M_PI));
}


template <typename T2> T2 BSM<T2>::C()
{
    T2 T = grealT();
    T2 S0 = gS0();
    T2 Q = gQ();
    return S0 * exp(-Q * T) * sncdf.cdf(d1()) - KPV() * sncdf.cdf(d2());
}

template <typename T2> T2 BSM<T2>::P()
{
    T2 T = grealT();
    T2 S0 = gS0();
    T2 Q = gQ();
    return -S0 * exp(-Q * T) * sncdf.cdf(-d1()) + KPV() * sncdf.cdf(-d2());
}



template <typename T2> T2 BSM<T2>::deltaC()
{
    return sncdf.cdf(d1());
}

template <typename T2> T2 BSM<T2>::deltaP()
{
    return deltaC() - 1.0;
}

template <typename T2> T2 BSM<T2>::gamma()
{
    T2 T = grealT();
    T2 S0 = gS0();
    T2 sigma = gSigma();
    return np(d1()) / (S0 * sigma * sqrt(T));
}

template <typename T2> T2 BSM<T2>::thetaP(bool trading_days)
{
    T2 T = grealT();
    T2 K = gK();
    T2 r = gR();
    return thetaC(trading_days) + r * K * exp(-r * T);
}

template <typename T2> T2 BSM<T2>::thetaC(bool trading_days)
{
    T2 T = grealT();
    T2 r = gR();
    T2 S0 = gS0();
    T2 K = gK();
    T2 sigma = gSigma();
    T2 theta = -(S0 * np(d1()) * sigma / (2 * sqrt(T))) - r * K * exp(-r * T) * sncdf.cdf(d2());

    if (trading_days)
    {
        return theta / 252;
    }
    return theta / 365;
}

template <typename T2> T2 BSM<T2>::vega()
{
    T2 T = grealT();
    T2 S0 = gS0();
    return S0 * sqrt(T) * np(d1());
}

template <typename T2> T2 BSM<T2>::rhoC()
{
    T2 T = grealT();
    T2 K = gK();
    T2 r = gR();
    return K * T * exp(-r * T) * sncdf.cdf(d2());
}

template <typename T2> T2 BSM<T2>::rhoP()
{
    T2 T = grealT();
    T2 K = gK();
    T2 r = gR();
    return K * T * exp(-r * T) * sncdf.cdf(-d2());
}


template class BSM<double>;
template class BSM<float>;
