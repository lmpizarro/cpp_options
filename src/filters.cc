#include "filters.h"
#include <iostream>
#include <fstream>

void Filter::run(){};

FirFilter::FirFilter(FirCoeffs *coeffs, Signal *inp, Signal *out)
{
    input = inp;
    coefficients = coeffs;
    output = out;
}

void FirFilter::run()
{
    for (size_t i = 2; i < input->length(); i++)
    {
        float result = 0.0;
        for (size_t j = 0; j < coefficients->getLength(); j++)
        {
            if (i > j)
            {
                result += coefficients->getCoefficient(j) * input->getPosition(i - j);
            }
        }
        output->data[1] = output->data[2];
        output->data[i] = result;
    }
}

void Filter::csvResult(const std::string filename)
{
    std::fstream fout;
    fout.open(filename, std::ios::out);
    std::string out_str = "t,inp,out\n";
    for (size_t i = 0; i < getOutput()->length(); i++)
    {
        float inp__ = getInput()->getPosition(i);
        float out__ = getOutput()->getPosition(i);
        out_str += std::to_string(i) + "," + std::to_string(inp__) + "," + std::to_string(out__) + "\n";
    }
    fout << out_str << std::endl;
    fout.close();
}

EMA::EMA(float a, Signal *inp, Signal *out)
{
    input = inp;
    output = out;
    alfa = a;
};

EMA::EMA(Signal *inp, Signal *out)
{
    input = inp;
    output = out;
};

void EMA::run()
{
    output->data[0] = 0;
    for (size_t i = 1; i < input->length(); i++)
    {
        output->data[i] = (1 - alfa) * output->data[i - 1] + alfa * input->getPosition(i);
    }
};

IEMA::IEMA(float a, Signal *inp, Signal *out) : EMA(a, inp, out){};

IEMA::IEMA(Signal *inp, Signal *out) : EMA(inp, out){};

void IEMA::run()
{
    EMA::run();
    for (size_t i =0; i < output->length(); i++){
        output->data[i] = input->data[i] - output->data[i];
    }
};
