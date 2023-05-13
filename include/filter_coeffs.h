#ifndef CALC_FRAC_HH
#define CALC_FRAC_HH

#include <memory>
#include <vector>

#include "signals.h"

using namespace std;

const int GRUNWALD_LETNIKOV_COEFS = 10;

class FirCoeffs
{
protected:
    unique_ptr<float[]> coefficients;
    size_t n_coefficients;

public:
    FirCoeffs(const size_t);

    friend ostream &operator<<(ostream &os, FirCoeffs &s);

    float &operator[](size_t i);
};

// Grunwald-Letnikov derivative
class FractionalDerivative : public FirCoeffs
{
private:
    float alfa;

public:
    FractionalDerivative(const float);
};

class FirFilter
{
protected:
    FirCoeffs *coefficients;
    Signal *input;
    Signal *output;

public:
    FirFilter(FirCoeffs *, Signal *, Signal *);
    void run();
};

#endif