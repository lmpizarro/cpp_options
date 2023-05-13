#include "filter_coeffs.h"
#include "signals.h"
#include <iostream>
#include <cmath>

using namespace std;

FirCoeffs::FirCoeffs(const size_t n)
{
    n_coefficients = n;

    coefficients = std::make_unique<float[]>(n_coefficients);
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

ostream &operator<<(ostream &os, FirCoeffs &s)
{
    os << "[ ";
    for (size_t i = 0; i < s.n_coefficients; i++)
    {
        os << s.coefficients[i] << " ";
    }
    os << "]" << endl;
    return os;
};

float &FirCoeffs::operator[](size_t i)
{
    if (i >= n_coefficients)
    {
        cout << "Index out of bounds " << n_coefficients << endl;
        return coefficients[0];
    }
    return coefficients[i];
}

FirFilter::FirFilter(FirCoeffs *coeffs, Signal *inp, Signal *out)
{
    input = inp;
    coefficients = coeffs;
    output = out;
}

void FirFilter::run(){
    for(size_t i = 0; i < input->getsize(); i++){
        output->data[i] = input->data[i];
    }
}