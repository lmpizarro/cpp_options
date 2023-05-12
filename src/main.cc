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
#include "calc_frac.h"

using namespace std;

const float ONE_DAY = 1.0 / 365.0;

int test()
{
    Hedge hedge(.3, ONE_DAY, .04, .06);
    NormalCDF ncdf(0.0, 1.0);
    StandardNormalCDF sncdf;
    Option option(49.0, 50.0, .3846, 0.05, .2, 0.0);

    cout << "d " << hedge.d() << endl;
    cout << "u " << hedge.u() << endl;
    cout << "p " << hedge.p() << endl;
    cout << "pp " << hedge.pp() << endl;
    cout << "ncdf " << ncdf.cdf(-0.0) << endl;
    cout << "sncdf " << sncdf.cdf(-0.0) << endl;
    cout << "d1 " << option.d1() << endl;
    cout << "d2 " << option.d2() << endl;
    cout << "N d1 " << sncdf.cdf(option.d1()) << endl;
    cout << "N d2 " << sncdf.cdf(option.d1()) << endl;
    cout << "Call " << option.C() << endl;
    cout << "Put " << option.P() << endl;
    cout << "delta Put " << option.deltaP() << endl;
    cout << "delta Call " << option.deltaC() << endl;
    cout << "gamma  " << option.gamma() << endl;
    cout << "thetaC  " << option.thetaC(true) << endl;
    cout << "rhoC  " << option.rhoC() << endl;
    cout << "rhoP  " << option.rhoP() << endl;
    cout << "vega  " << option.vega() << endl;

    ImpliedVolatility  Iv(&option);
    float price = 1.31;
    float iv = Iv.bisection(price, 0, 1);
    option.setIV(iv);
    cout << "Call IV calc bisection " << iv << " est price " << option.C() << "price " << price << endl;
    option.setIV(.5);
    iv = Iv.regulaFalsi(price, 0, 1);
    option.setIV(iv);
    cout << "Call IV calc regulaFalsi " << iv << " est price " << option.C() << " price " << price << endl;
    Signal sgnal(100, 10);

    Normal nrml(0, 1, 252);

    Uniform unfrm(0, 1, 10);

    Uniform un(unfrm);

    Uniform uu = un + unfrm;

    cout << uu << endl;
    cout << un << endl;
    cout << un[0] << endl;

    Sin price_t(49.0, 5, 1.0, 252);
    fstream fout;
    fout.open("datos.csv", ios::out);
    fout << option_csv_header() << endl;

    for (int i = 0; i < price_t.getsize(); i++)
    {
        float tt = (float)i / 252.0;
        float ttm = 1.0 - tt;
        if (ttm > 0)
        {
            Option option(price_t[i], 50.0, ttm, 0.05, .2, 0.03);
            fout << option << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}


int main()
{
    FractionalDerivative fracDev(.5);

    cout << fracDev << endl;
    // test();
}
