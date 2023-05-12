#include <iostream>
#include "option.h"

using namespace std;

int example()
{

    Option option(49.0, 50.0, .3846, 0.05, .2, 0.0);

    cout << option.gT() << "," << option.gS0() << "," << option.C() << ","
    << option.deltaC() << "," << option.gamma() << "," << option.thetaC(true) << endl;

    return 0;
}