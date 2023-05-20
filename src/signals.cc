#include "signals.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

Signal::Signal(const float a, const size_t s)
{
    length = s;
    data = std::make_unique<float[]>(length);
    for (size_t i = 0; i < length; i++)
    {
        data[i] = a;
    }
}

Signal::Signal(const Signal &s)
{
    length = s.length;
    data = std::make_unique<float[]>(length);
    for (size_t i = 0; i < length; i++)
    {
        data[i] = s.data[i];
    }
}

Signal Signal::operator+(const Signal &s)
{
    Signal sum(s);
    for (size_t i = 0; i < s.length; i++)
    {
        sum.data[i] = this->data[i] + s.data[i];
    }
    return sum;
}

float &Signal::operator[](size_t i)
{
    if (i >= length)
    {
        cout << "Index out of bounds " << length << endl;
        return data[0];
    }
    return data[i];
}


float Signal::getPosition(size_t pos){
    if (pos < getLength()){
        return data[pos];
    } else {
        return 0;
    }
}

Uniform Uniform::operator+(const Uniform &s)
{
    Uniform sum(s);
    for (size_t i = 0; i < s.length; i++)
    {
        sum.data[i] = this->data[i] + s.data[i];
    }
    return sum;
}

Sin::Sin(const float cc, const float amp, const float cycles, const size_t s) : Signal(cc, s)
{
    for (size_t i = 0; i < length; i++)
    {
        data[i] += amp * sin(2 * M_PI * cycles * i / length);
    }
}

Normal::Normal(const float lo, const float sc, const size_t s) : Signal(0, s)
{
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(lo, sc);
    for (size_t i = 0; i < length; i++)
    {
        data[i] += distribution(generator);
    }
}

Uniform::Uniform(const float lo, const float up, const size_t s) : Signal(0, s)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(lo, up);
    for (size_t i = 0; i < length; i++)
    {
        data[i] += distribution(generator);
    }
}


GBM::GBM(const float S0, const float mu, const float vol, const float T, const size_t length): Signal(0,length){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    float dt = T / length;
    float price = S0;

    for (size_t i = 0; i < length; ++i) {
        float epsilon = distribution(gen);
        float driftTerm = mu * price * dt;
        float volatilityTerm = vol * price * std::sqrt(dt) * epsilon;

        price = price * std::exp(driftTerm + volatilityTerm);
        data[i] = price;
    }
}

ostream &operator<<(ostream &os, Signal &s)
{
    os << "[ ";
    for (size_t i = 0; i < s.length; i++)
    {
        os << s.data[i] << " ";
    }
    os << "]" << endl;
    return os;
}
