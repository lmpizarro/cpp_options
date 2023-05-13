#ifndef SIGNALS_HH
#define SIGNALS_HH

#include <memory>
#include <vector>
using namespace std;

class Signal
{
public:
    unique_ptr<float[]> data;

    size_t size;
    
    /// @brief create a constant signal
    /// @param amp
    /// @param size
    Signal(const float amp, const size_t size);
    ~Signal() { data.reset(); };

    friend ostream &operator<<(ostream &os, Signal &s);


    Signal operator+(const Signal &s);

    Signal(const Signal &s);

    float &operator[](size_t i);

    size_t getsize() { return size; }

};

class Sin : public Signal
{
public:
    Sin(const float cc, const float amp, const float cycles, const size_t size);
};

class Normal : public Signal
{
public:
    Normal(const float loc, const float scale, const size_t size);
};

class Uniform : public Signal
{
public:
    Uniform(const float lo, const float up, const size_t size);
    Uniform operator+(const Uniform &s);
};

#endif