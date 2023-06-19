#ifndef __OPT_SIM_H
#define __OPT_SIM_H
#include "signals.h"
#include "option.h"

class Simulator
{
private:
    BSM option;
    Signal S;
    Linear time;

public:
    Simulator(BSM &opt, Signal & signal, Linear & lin);
    void run(std::string);
};

#endif