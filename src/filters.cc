#include "filters.h"
#include <iostream>
#include <fstream>

using namespace std;

void Filter::run(){};

FirFilter::FirFilter(FirCoeffs *coeffs, Signal *inp, Signal *out)
{
    input = inp;
    coefficients = coeffs;
    output = out;
}

void FirFilter::run()
{
    for (size_t i = 0; i < input->getLength(); i++)
    {
        float result = 0.0;
        for (size_t j = 0; j < coefficients->getLength(); j++)
        {
            if (i > j)
            {
                result += coefficients->getCoefficient(j) * input->getPosition(i - j);
            }
        }

        output->data[i] = result;
    }
}

void FirFilter::csvResult(const string filename)
{
    fstream fout;
    fout.open(filename, ios::out);
    std::string out_str = "t,inp,out\n";
    for (size_t i = 0; i < getOutput()->getLength(); i++)
    {
        float inp__ = getInput()->getPosition(i);
        float out__ = getOutput()->getPosition(i);
        out_str += std::to_string(i) + "," + std::to_string(inp__) + "," + std::to_string(out__) + "\n";
    }
    fout << out_str << endl;
    fout.close();
}
