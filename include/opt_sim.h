#ifndef __OPT_SIM_H
#define __OPT_SIM_H
#include "signals.h"
#include "option.h"

class Simulator
{
private:
    BSM *option;
    Signal *S;

public:
    Simulator(BSM *opt, Signal * signal);
    void run(std::string);
};

#endif