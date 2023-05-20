#include "aux.h"
#include <iostream>

using std::string;

string option_csv_header()
{
    string str = "T,S0,C,deltaC,thetaC,rhoC,P,deltaP,thetaP,rhoP,gamma,vega";

    return str;
}