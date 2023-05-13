#ifndef SIGNALS_HH
#define SIGNALS_HH

#include <memory>
#include <vector>
using namespace std;
/*
 */
class Signal
{
public:
    unique_ptr<float[]> data;

    size_t length;
    /*
    /// @brief Constructor create a constant signal
    /// @param amp  amplitude of the signal
    /// @param length duration
    */
    Signal(const float amp, const size_t length);

    ~Signal() { data.reset(); };

    friend ostream &operator<<(ostream &os, Signal &s);

    Signal operator+(const Signal &s);
    /// @brief construct a constant signal from another signal
    /// @param sgnal another signal object
    Signal(const Signal &sgnal);

    float &operator[](size_t i);


    /// @brief get the length of the signal
    /// @return the length
    size_t getLength() { return length; }

    float getPosition(size_t pos);
};

class Sin : public Signal
{
public:
    /// @brief create a sinusoide signal
    /// @param cc continuous value
    /// @param amp amplitude
    /// @param cycles number of 2 pi cycles
    /// @param length of the signal
    Sin(const float cc, const float amp, const float cycles, const size_t length);
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