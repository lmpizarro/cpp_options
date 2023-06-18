
#ifndef __OPTION_H
#define __OPTION_H
#include <iostream>
#include "cdf.h"

const float ONE_DAY = 1.0 / 365.0;

class Option
{
public:
    Option();
    Option(const float &_S0, const float &_K, const float &_T,
           const float &_r, const float &_sigma, const float &_Q);
    Option(const Option &_option);
    Option &operator=(const Option &rhs);
    float gS0() const { return S0; };
    float gK() const { return K; };
    float gexT() const { return T; }
    float gSigma() const { return sigma; }
    float gQ() const { return Q; }
    float gR() const { return r; }

    virtual float C() const = 0;
    virtual float P() const = 0;
    virtual float deltaC() const = 0;
    virtual float deltaP() const = 0;
    virtual float thetaC(bool) const = 0;
    virtual float thetaP(bool) const = 0;
    virtual float rhoC() const = 0;
    virtual float rhoP() const = 0;
    virtual float vega() const = 0;
    virtual float gamma() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Option &s);

    virtual void print(std::ostream &o) const = 0;

protected:
    float S0, K, T, r, sigma, Q;

private:
    void copy(const Option &);
};

inline std::ostream &operator<<(std::ostream &os, const Option &option)
{
    option.print(os);
    return os;
}

class BSM : public Option
{
private:
    float simTime = 0;
    StandardNormalCDF sncdf;
    float np(float x) const;
    float KPV() const;
    float grealT() const;

public:
    BSM(const float &S0, const float &K, const float &T,
        const float &r, const float &sigma, const float &Q);
    float d1() const;
    float d2() const;
    float C() const;
    float P() const;
    float deltaC() const;
    float deltaP() const;
    float thetaC(bool) const;
    float thetaP(bool) const;
    float rhoC() const;
    float rhoP() const;
    float vega() const;
    float gamma() const;
    void setIV(float);
    float diffPriceC(float, float);
    float diffPriceP(float, float);

    void setSimTime(const float);
    float getSimTime() const { return simTime; };

    void print(std::ostream &o) const;
};

#endif