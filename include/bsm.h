#ifndef BSM_H
#define BSM_H

#include "option.h"

template <typename T2>
class BSM: public Option<T2>
{
private:
    StandardNormalCDF<T2> sncdf;
    T2 np(T2 x);
    T2 KPV();
    T2 d1();
    T2 d2();

public:
    BSM(T2 S0, T2 K, T2 T, T2 r, T2 sigma, T2 Q);
    T2 C() override;
    T2 P() override;
    T2 deltaC() override;
    T2 deltaP() override;
    T2 thetaC(bool) override;
    T2 thetaP(bool) override;
    T2 rhoC() override;
    T2 rhoP() override;
    T2 vega() override;
    T2 gamma() override;

    T2 gK()const{return Option<T2>::gK();};
    T2 gS0()const{return Option<T2>::gS0();};
    T2 gR()const{return Option<T2>::gR();};
    T2 gQ()const{return Option<T2>::gQ();};
    T2 gSigma()const{return Option<T2>::gSigma();};
    T2 grealT()const{return Option<T2>::grealT();};

};
#endif