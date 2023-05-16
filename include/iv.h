#ifndef IV_H
#define IV_H

#include "option.h"

template <typename Type> class ImpliedVolatility{
    private:
        Option<Type> *option;
    public:
        ImpliedVolatility(Option<Type> *);

        Type bisection(Type, Type, Type);
        Type regulaFalsi(Type, Type, Type);
};
#endif