#include "iv.h"
#include "option.h"
/*
    notes:
    https://www.mathworks.com/moler/chapters.html
*/
template <typename Type> ImpliedVolatility<Type>::ImpliedVolatility(Option<Type> *optn)
{
    option = optn;
}

template <typename Type> Type ImpliedVolatility<Type>::bisection(Type p, Type s1, Type s2)
{
    if (option->diffPriceC(p, s1) * option->diffPriceC(p, s2) >= 0)
    {
        cout << "You have not assumed right a and b\n";
        return 0;
    }

    Type sm = s1;
    while ((s2 - s1) >= 0.001)
    {
        // Find middle point
        sm = (s2 + s1) / 2;

        // Check if middle point is root
        if (option->diffPriceC(p, sm) == 0.0)
            break;

        // Decide the side to repeat the steps
        else if (option->diffPriceC(p, sm) * option->diffPriceC(p, s1) < 0)
            s2 = sm;
        else
            s1 = sm;
    }
    return sm;
}

template <typename Type> Type ImpliedVolatility<Type>::regulaFalsi(Type p, Type s1, Type s2)
{
    if (option->diffPriceC(p, s1) * option->diffPriceC(p, s2) >= 0)
    {
        cout << "You have not assumed right a and b\n";
        return 0;
    }

    Type sm = s1;

    for (int i = 0; i < 1000; i++)
    {
        // Find the point that touches x axis
        sm = (s1 * option->diffPriceC(p, s2) - s2 * option->diffPriceC(p, s1)) / (option->diffPriceC(p, s2) - option->diffPriceC(p, s1));

        // Check if the above found point is root
        if (option->diffPriceC(p, sm) == 0)
            break;

        // Decide the side to repeat the steps
        else if (option->diffPriceC(p, sm) * option->diffPriceC(p, sm) < 0)
            s2 = sm;
        else
            s1 = sm;
    }
    return sm;
}


template class ImpliedVolatility<float>;
template class ImpliedVolatility<double>;
