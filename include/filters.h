#ifndef FILTERS_HH
#define FILTERS_HH

#include "filter_coeffs.h"
#include "signals.h"

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