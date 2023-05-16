#include <cmath>
#include <iostream>
#include "option.h"

using namespace std;

template <typename Type> Option<Type>::Option(Type s0, Type k, Type t, Type rr, Type sma, Type q)
{
    S0 = s0;
    K = k;
    r = rr;
    sigma = sma;
    T = t;
    Q = q;
}

template <typename Type> Type Option<Type>::grealT(){
    if (simTime < T){
        return T - simTime;
    }
    return 0;
};

template <typename Type> void Option<Type>::setSimTime(const Type t){
    simTime = t;
};

template <typename Type> Type Option<Type>::d1()
{
    Type T = grealT();
    return (log(S0 / K) + (r - Q + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
}

template <typename Type> Type Option<Type>::d2()
{
    Type T = grealT();
    return d1() - sigma * sqrt(T);
}

template <typename Type> Type Option<Type>::C()
{
    Type T = grealT();
    return S0 * exp(-Q * T) * sncdf.cdf(d1()) - KPV() * sncdf.cdf(d2());
}

template <typename Type> Type Option<Type>::P()
{
    Type T = grealT();
    return -S0 * exp(-Q * T) * sncdf.cdf(-d1()) + KPV() * sncdf.cdf(-d2());
}

template <typename Type> Type Option<Type>::KPV()
{
    Type T = grealT();
    return K * exp(-r * T);
}



template <typename Type> Type Option<Type>::deltaC()
{
    return sncdf.cdf(d1());
}

template <typename Type> Type Option<Type>::deltaP()
{
    return deltaC() - 1.0;
}

template <typename Type> Type Option<Type>::np(Type x)
{
    return exp(pow(x, 2) / 2) / (sqrt(2 * M_PI));
}

template <typename Type> Type Option<Type>::gamma()
{
    Type T = grealT();
    return np(d1()) / (S0 * sigma * sqrt(T));
}

template <typename Type> Type Option<Type>::thetaP(bool trading_days)
{
    Type T = grealT();
    return thetaC(trading_days) + r * K * exp(-r * T);
}

template <typename Type> Type Option<Type>::thetaC(bool trading_days)
{
    Type T = grealT();
    Type theta = -(S0 * np(d1()) * sigma / (2 * sqrt(T))) - r * K * exp(-r * T) * sncdf.cdf(d2());

    if (trading_days)
    {
        return theta / 252;
    }
    return theta / 365;
}

template <typename Type> Type Option<Type>::vega()
{
    Type T = grealT();
    return S0 * sqrt(T) * np(d1());
}

template <typename Type> Type Option<Type>::rhoC()
{
    Type T = grealT();
    return K * T * exp(-r * T) * sncdf.cdf(d2());
}

template <typename Type> Type Option<Type>::rhoP()
{
    Type T = grealT();
    return K * T * exp(-r * T) * sncdf.cdf(-d2());
}

template <typename Type> void Option<Type>::setIV(Type sma)
{
    sigma = sma;
}

template <typename Type> Type Option<Type>::diffPriceC(Type pc, Type s)
{
    setIV(s);
    return pc - C();
}

template <typename Type> Type Option<Type>::diffPriceP(Type pp, Type s)
{
    setIV(s);
    return pp - P();
}


ostream &operator<<(ostream &os, Option<float> &s)
{
    os << s.getSimTime() << "," << s.S0 << ","
       << s.C() << "," << s.deltaC() << "," << s.thetaC(true) << "," << s.rhoC() << ","
       << s.P() << "," << s.deltaP() << "," << s.thetaP(true) << "," << s.rhoP() << ","
       << s.gamma()  << "," << s.vega();
    return os;
};

template class Option<float>;
template class Option<double>;


