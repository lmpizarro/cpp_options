#ifndef CALC_FRAC_HH
#define CALC_FRAC_HH

#include <memory>
#include <vector>

using namespace std;

// Grunwald-Letnikov derivative
class FractionalDerivative
{
private:
    float alfa;
    unique_ptr<float[]> coefficients;
    const int size = 10;

public:
    FractionalDerivative(const float);

    friend ostream &operator<<(ostream &os, FractionalDerivative &s);
};

#endif