#include <cmath>
#include "hedge.h"

Hedge::Hedge(float s, float d, float rate, float mmu)
{
    sigma = s;
    deltaT = d;
    rFr = rate;
    mu = mmu;
}

float Hedge::u()
{
    return exp(sigma * sqrt(deltaT));
}

float Hedge::d()
{
    return exp(-sigma * sqrt(deltaT));
}

float Hedge::p()
{
    return (exp(rFr * deltaT) - d()) / (u() - d());
}

float Hedge::pp()
{
    return (exp(mu * deltaT) - d()) / (u() - d());
}
