#ifndef OPT_SIM_H
#define OPT_SIM_H
#include "signals.h"
#include "bsm.h"

using namespace std;

class Simulator
{
private:
    BSM<float> *option;
    Signal *S;

public:
    Simulator(BSM<float> *opt, Signal * signal);
    void run(string);
};

#endif