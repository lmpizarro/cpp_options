#ifndef __SIGNALS_H
#define __SIGNALS_H

#include <memory>
#include <vector>
/*
 */
class Signal
{
public:
    std::unique_ptr<float[]> data;

    size_t _length;
    /*
    /// @brief Constructor create a constant signal
    /// @param amp  amplitude of the signal
    /// @param length duration
    */
    Signal(const float amp, const size_t length);
    Signal operator+(const Signal &s);
    Signal &operator=(const Signal &s);
    /// @brief construct a constant signal from another signal
    /// @param sgnal another signal object
    Signal(const Signal &sgnal);
    ~Signal() { data.reset(); };

    float &operator[](size_t i);

    /// @brief get the length of the signal
    /// @return the length
    size_t length() { return _length; }

    float getPosition(size_t pos);

    void generate();
    friend std::ostream &operator<<(std::ostream &os, Signal &s);
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

class GBM : public Signal
{
public:
    GBM(const float S0, const float mu, const float vol, const float dt, const size_t size);
};

class Heston : public Signal
{
private:
    double rho, kappa, theta, sigma, r;

    std::unique_ptr<double[]> zv;
    std::unique_ptr<double[]> zs;
    void update_zv_zs();

public:
    Heston();
    Heston(const float &rh, const float &kapp, const float &thet,
           const float &sgm, const float &rr, const size_t &N);
    void generate(const double v0, const double s0, const double dt);
    ~Heston()
    {
        zv.reset();
        zs.reset();
    }
};

class Linear : public Signal
{
public:
    Linear(const float &init, const float &end, size_t &N);
};

#endif