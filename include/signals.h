#ifndef SIGNALS_HH
#define SIGNALS_HH

#include <memory>
#include <vector>
using namespace std;

class Signal
{
public:
    unique_ptr<float[]> data;

    int size;

    Signal(const float, const int size);

    friend ostream &operator<<(ostream &os, Signal &s);

    ~Signal() { data.reset(); };

    Signal operator+(const Signal &s);

    Signal(const Signal &s);

    float &operator[](int i);

    int getsize() { return size; }
};

class Sin : public Signal
{
public:
    Sin(const float cc, const float amp, const float cycles, const int size);
};

class Normal : public Signal
{
public:
    Normal(const float loc, const float scale, const int size);
};

class Uniform : public Signal
{
public:
    Uniform(const float lo, const float up, const int size);
    Uniform operator+(const Uniform &s);
};

#endif