#include "filters.h"

using namespace std;

FirFilter::FirFilter(FirCoeffs *coeffs, Signal *inp, Signal *out)
{
    input = inp;
    coefficients = coeffs;
    output = out;
}

void FirFilter::run(){
    for(size_t i = 0; i < input->getLength(); i++){
        float result = 0.0;
        for (size_t j=0; j < coefficients->getLength(); j++){
            if (i>j){
                result += coefficients->getCoefficient(j) * input->getPosition(i-j);
            }
        }

        output->data[i] = result;
    }
}

