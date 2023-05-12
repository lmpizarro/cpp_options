#include "calc_frac.h"
#include <iostream>
#include <cmath>

using namespace std;

FractionalDerivative::FractionalDerivative(const float ord)
{
    float factorial = 1.0;
    alfa = ord;
    coefficients = std::make_unique<float[]>(size);
    coefficients[0] = 1.0;
    for (int k = 1; k < size; k++)
    {
        factorial *= k;
        coefficients[k] = pow(-1,k)*std::tgamma(alfa + 1)/std::tgamma(alfa -k + 1) / factorial;
    }
};


ostream &operator<<(ostream &os, FractionalDerivative &s)
{
    os << "[ ";
    for (int i = 0; i < s.size; i++)
    {
        os << s.coefficients[i] << " ";
    }
    os << "]" << endl;
    return os;
};