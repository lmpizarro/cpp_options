#ifndef __CALC_FRAC_H
#define __CALC_FRAC_H

#include <memory>
#include <vector>

#include "signals.h"

const int GRUNWALD_LETNIKOV_COEFS = 10;

class FirCoeffs
{
protected:
    std::unique_ptr<float[]> coefficients;
    size_t n_coefficients;

public:
    FirCoeffs(const size_t);

    friend std::ostream &operator<<(std::ostream &os, FirCoeffs &s);

    float &operator[](size_t i);
    float getCoefficient(size_t position);
    size_t getLength(){return n_coefficients;};
    ~FirCoeffs() { coefficients.reset(); };

};

// Grunwald-Letnikov derivative
class FractionalDerivative : public FirCoeffs
{
private:
    float alfa;

public:
    FractionalDerivative(const float);
};

class WMA4:public FirCoeffs{
    public:
    WMA4();
};
#endif

