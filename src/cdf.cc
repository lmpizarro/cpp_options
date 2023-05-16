#include <cmath>
#include "cdf.h"

using namespace std;

template <typename Type> NormalCDF<Type>::NormalCDF(Type l, Type s)
{
    loc = l;
    scale = s;
}

template <typename Type> Type NormalCDF<Type>::cdf(Type x)
{
    Type value;
    value = (x - loc) / (scale * sqrt(2));

    return 0.5 * (1 + erf(value));
};

template <typename Type> StandardNormalCDF<Type>::StandardNormalCDF(void) : NormalCDF<Type>(0, 1) {}

template <typename Type> Type StandardNormalCDF<Type>::cdf(Type x)
{
    return NormalCDF<Type>::cdf(x);
}


template class NormalCDF<float>;
template class NormalCDF<double>;
template class StandardNormalCDF<float>;
template class StandardNormalCDF<double>;
