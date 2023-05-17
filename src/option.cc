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

template <typename Type> Type Option<Type>::grealT()const{
    if (simTime < T){
        return T - simTime;
    }
    return 0;
};

template <typename Type> void Option<Type>::setSimTime(const Type t){
    simTime = t;
};

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

/*
https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function
*/
template class Option<float>;
template class Option<double>;


