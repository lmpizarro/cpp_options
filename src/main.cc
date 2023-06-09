#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "signals.h"
#include "aux.h"
#include "filter_coeffs.h"
#include "filters.h"
#include "examples/ex_frac_dev.h"
#include "examples/ex_option.h"


int test_wma(){
    WMA4 wma;
    const int length = 252;
    Normal nrml(0, 1, length);
    Signal out(0, length);
    FirFilter firfilter(&wma, &nrml, &out);
    firfilter.run();
    firfilter.csvResult("filter_out.csv");

    return 0;
}


int test_ema(){
    const int length = 252;
    Normal nrml(0, 1, length);
    Signal out(0, length);
    EMA ema(&nrml, &out);
    ema.run();
    ema.csvResult("filter_out.csv");

    return 0;
}

int test_iema(){
    const int length = 252;
    Normal nrml(0, 1, length);
    GBM inp(1, 0.03, 0.2, 1.0/252.0, 252);
    Signal out(0, length);
    IEMA ema(&inp, &out);
    ema.run();
    ema.csvResult("filter_out.csv");

    return 0;
}


int main(){
    ex_sim_option();
    Heston hst;
    hst.generate(.3, 100, 1.0/252.0);
    std::cout << hst << std::endl;
    return 0;
}