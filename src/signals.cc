#include "signals.h"
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>    // std::max


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
        std::cout << "Index out of bounds " << length << std::endl;
        return data[0];
    }
    return data[i];
}

float Signal::getPosition(size_t pos)
{
    if (pos < getLength())
    {
        return data[pos];
    }
    else
    {
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
};

GBM::GBM(const float S0, const float mu, const float vol, const float dt, const size_t length) : Signal(0, length)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    float price = S0;

    for (size_t i = 0; i < length; ++i)
    {
        float epsilon = distribution(gen);
        float driftTerm = mu * price * dt;
        float volatilityTerm = vol * price * std::sqrt(dt) * epsilon;

        price = price * std::exp(driftTerm + volatilityTerm);
        data[i] = price;
    }
}
Heston::Heston() : Heston(.8, 21, .1, .3, .09, 21)
{
}

Heston::Heston(const float rh, const float kapp, const float thet,
               const float sgm, const float rr, const size_t N) : Signal(0, N)
{
    rho = rh;
    kappa = kapp;
    theta = thet;
    sigma = sgm;
    r = rr; // risk neutral meassure
    length = N;

    zv = std::make_unique<double[]>(length);
    zs = std::make_unique<double[]>(length);
    update_zv_zs();
}

void Heston::update_zv_zs(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    // std::default_random_engine de(time(0)); //seed
    // std::normal_distribution<double> nd(0.0, 1.0); //mean followed by stdiv

    for (size_t i=0; i < length; ++i){
        zv[i] = distribution(rd);
        zs[i] = rho * zv[i] + sqrt(1- pow(rho, 2))*distribution(rd);
    }
}

void Heston::generate(const double v0, const double s0, const double dt)
{
    double v1;
    double vi = v0;
    update_zv_zs();
    data[0] = s0;
    for (size_t i = 1; i < length; i++)
    {
        v1 = vi + kappa * (theta - vi)*dt + sigma * std::sqrt(vi * dt) * zv[i] + .25 * std::pow(sigma, 2.0) * dt * (std::pow(zv[i], 2.0) - 1.0);

        vi = std::max(0.0, (double)v1);
        data[i] = data[i-1] * (1 + r * dt + std::sqrt(vi * dt) * zs[i]) + .25 * std::pow(data[i-1],2)*dt*(std::pow(zs[i-1],2) -1);

        // cout << i << " " << vi  << " " << data[i] << endl;
    }
    // cout << "v0 " << v0 << " s0 " << s0 << " dt " << dt << endl;
    // cout << "rho " << rho << " kappa " << kappa << " theta " << theta << " sigma " << sigma << " rr " << r << endl;
}

std::ostream &operator<<(std::ostream &os, Signal &s)
{
    os << "[ ";
    for (size_t i = 0; i < s.length; i++)
    {
        os << s.data[i] << " ";
    }
    os << "]" << std::endl;
    return os;
};
