#ifndef __FILTERS_H
#define __FILTERS_H

#include "filter_coeffs.h"
#include "signals.h"

class Filter
{

protected:
    Signal *input;
    Signal *output;

public:
    virtual void run();
    Signal *getInput() { return input; };
    Signal *getOutput() { return output; };
    void csvResult(const std::string);
};

class FirFilter : public Filter
{
protected:
    FirCoeffs *coefficients;

public:
    FirFilter(FirCoeffs *, Signal *, Signal *);
    void run();
};

class EMA : public Filter
{
protected:
    float alfa = .5;

public:
    EMA(const float alf, Signal*, Signal*);
    EMA(Signal*, Signal*);
    void run();
};

class IEMA : public EMA
{

public:
    IEMA(const float alf, Signal*, Signal*);
    IEMA(Signal*, Signal*);
    void run();
};


#endif