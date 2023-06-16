#include <cmath>
#include "cdf.h"

NormalCDF::NormalCDF(float l, float s)
{
    loc = l;
    scale = s;
}

float NormalCDF::cdf(float x)
{
    float value;
    value = (x - loc) / (scale * sqrt(2));

    return 0.5 * (1 + erf(value));
};

StandardNormalCDF::StandardNormalCDF(void) : NormalCDF(0, 1) {}

float StandardNormalCDF::cdf(float x)
{
    return NormalCDF::cdf(x);
}
