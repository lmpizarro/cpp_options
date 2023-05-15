#include <iostream>
#include <string>
#include <string>
#include <cmath>
#include "signals.h"
#include "aux.h"
#include "filters.h"
#include "ex_frac_dev.h"

using namespace std;

int ex_fracdev()
{
    cout << "jjj" ;
    FractionalDerivative fracDev(.99999);

    Sin inp(1,1,1,100);
    Signal out(0, 100);
    FirFilter firfilter(&fracDev,&inp, &out);
    firfilter.run();

    cout << fracDev << endl;
    cout << *firfilter.getOutput() << endl;
    cout << *firfilter.getInput() << endl;
    firfilter.csvResult("filter_out.csv");

    return 0;
}

