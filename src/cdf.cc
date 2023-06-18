#include <cmath>
#include "cdf.h"

NormalCDF::NormalCDF(const float l, const float s)
{
    loc = l;
    scale = s;
}

float NormalCDF::cdf(const float x) const
{
    float value;
    value = (x - loc) / (scale * sqrt(2));

    return 0.5 * (1 + erf(value));
};

StandardNormalCDF::StandardNormalCDF(void) : NormalCDF(0, 1) {}

float StandardNormalCDF::cdf(const float x) const
{
    return NormalCDF::cdf(x);
}
