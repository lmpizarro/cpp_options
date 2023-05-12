#ifndef IV_H
#define IV_H

#include "option.h"

class ImpliedVolatility{
    private:
        Option *option;
    public:
        ImpliedVolatility(Option *);

        float bisection(float, float, float);
        float regulaFalsi(float, float, float);
};
#endif