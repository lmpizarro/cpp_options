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

using namespace std;


int test_wma(){
    WMA wma;
    const int length = 252;
    Normal nrml(0, 1, length);
    Signal out(0, length);
    FirFilter firfilter(&wma, &nrml, &out);
    firfilter.run();
    firfilter.csvResult("filter_out.csv");

    return 0;
}


int main(){
    test_wma();
    return 0;
}