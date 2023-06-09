#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "option.h"
#include "hedge.h"
#include "signals.h"
#include "aux.h"
#include "iv.h"
#include "ex_option.h"
#include "opt_sim.h"



int ex_option_0()
{

    BSM option(49.0, 50.0, .3846, 0.05, .2, 0.0);

    std::cout << option.gexT() << "," << option.gS0() << "," << option.C() << ","
    << option.deltaC() << "," << option.gamma() << "," << option.thetaC(true) << std::endl;

    return 0;
}

int ex_option()
{
    Hedge hedge(.3, ONE_DAY, .04, .06);
    NormalCDF ncdf(0.0, 1.0);
    StandardNormalCDF sncdf;
    BSM option(49.0, 50.0, .3846, 0.05, .2, 0.0);

    std::cout << "d " << hedge.d() << std::endl;
    std::cout << "u " << hedge.u() << std::endl;
    std::cout << "p " << hedge.p() << std::endl;
    std::cout << "pp " << hedge.pp() << std::endl;
    std::cout << "ncdf " << ncdf.cdf(-0.0) << std::endl;
    std::cout << "sncdf " << sncdf.cdf(-0.0) << std::endl;
    std::cout << "d1 " << option.d1() << std::endl;
    std::cout << "d2 " << option.d2() << std::endl;
    std::cout << "N d1 " << sncdf.cdf(option.d1()) << std::endl;
    std::cout << "N d2 " << sncdf.cdf(option.d1()) << std::endl;
    std::cout << "Call " << option.C() << std::endl;
    std::cout << "Put " << option.P() << std::endl;
    std::cout << "delta Put " << option.deltaP() << std::endl;
    std::cout << "delta Call " << option.deltaC() << std::endl;
    std::cout << "gamma  " << option.gamma() << std::endl;
    std::cout << "thetaC  " << option.thetaC(true) << std::endl;
    std::cout << "rhoC  " << option.rhoC() << std::endl;
    std::cout << "rhoP  " << option.rhoP() << std::endl;
    std::cout << "vega  " << option.vega() << std::endl;

    ImpliedVolatility  Iv(&option);
    float price = 1.31;
    float iv = Iv.bisection(price, 0, 1);
    option.setIV(iv);
    std::cout << "Call IV calc bisection " << iv << " est price " << option.C() << "price " << price << std::endl;
    option.setIV(.5);
    iv = Iv.regulaFalsi(price, 0, 1);
    option.setIV(iv);
    std::cout << "Call IV calc regulaFalsi " << iv << " est price " << option.C() << " price " << price << std::endl;
    Signal sgnal(100, 10);

    Normal nrml(0, 1, 252);

    Uniform unfrm(0, 1, 10);

    Uniform un(unfrm);

    Uniform uu = un + unfrm;

    std::cout << uu << std::endl;
    std::cout << un << std::endl;
    std::cout << un[0] << std::endl;
    return 0;
};

int ex_sim_option(){
    size_t length = 252;
    Sin price_t(49.0, 0, 1.0, length);
    BSM option(49, 50.0, 1.0, 0.05, .2, 0.03);
    Linear time(0.0, 1.0, length);
    Simulator sim(option, price_t, time);
    sim.run("datos.csv");
    return 0;
}

