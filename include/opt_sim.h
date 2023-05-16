#ifndef OPT_SIM_H
#define OPT_SIM_H
#include "signals.h"
#include "option.h"

using namespace std;

class Simulator
{
private:
    Option<float> *option;
    Signal *S;

public:
    Simulator(Option<float> *opt, Signal * signal);
    void run(string);
};

#endif