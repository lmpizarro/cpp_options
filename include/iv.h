#ifndef IV_H
#define IV_H

#include "option.h"

class ImpliedVolatility{
    private:
        BSM *option;
    public:
        ImpliedVolatility(BSM *);

        float bisection(float, float, float);
        float regulaFalsi(float, float, float);
};
#endif