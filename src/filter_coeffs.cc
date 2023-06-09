#include "filter_coeffs.h"
#include "signals.h"
#include <iostream>
#include <cmath>


FirCoeffs::FirCoeffs(const size_t n)
{
    n_coefficients = n;

    coefficients = std::make_unique<float[]>(n_coefficients);
}

float FirCoeffs::getCoefficient(size_t pos){
    if (pos < getLength()){
        return coefficients[pos];
    }else{
        return 0;
    }
}

FractionalDerivative::FractionalDerivative(const float ord) : FirCoeffs(GRUNWALD_LETNIKOV_COEFS)
{
    float factorial = 1.0;
    alfa = ord;
    coefficients[0] = 1.0;
    for (size_t k = 1; k < n_coefficients; k++)
    {
        factorial *= k;
        coefficients[k] = pow(-1, k) * std::tgamma(alfa + 1) / std::tgamma(alfa - k + 1) / factorial;
    }
};

WMA4::WMA4():FirCoeffs(4){
    coefficients[0]  = 4.0/10.0;
    coefficients[1]  = 3.0/10.0;
    coefficients[2]  = 2.0/10.0;
    coefficients[3]  = 1.0/10.0;
};

std::ostream &operator<<(std::ostream &os, FirCoeffs &s)
{
    os << "[ ";
    for (size_t i = 0; i < s.n_coefficients; i++)
    {
        os << s.coefficients[i] << " ";
    }
    os << "]" << std::endl;
    return os;
};

float &FirCoeffs::operator[](size_t i)
{
    if (i >= n_coefficients)
    {
        std::cout << "Index out of bounds " << n_coefficients << std::endl;
        return coefficients[0];
    }
    return coefficients[i];
}

