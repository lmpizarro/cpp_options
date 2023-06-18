#include <iostream>
#include <string>
#include <string>
#include <cmath>
#include "signals.h"
#include "aux.h"
#include "filters.h"
#include "ex_frac_dev.h"


int ex_fracdev()
{
    size_t length = 252;
    FractionalDerivative fracDev(.999999);


    Sin inp(0.0, 1.0, 1.0, length);
    Signal out(0, length);
    FirFilter firfilter(&fracDev,&inp, &out);
    firfilter.run();

    std::cout << fracDev << endl;
    std::cout << out << endl;
    firfilter.csvResult("filter_out.csv");

    return 0;
}

