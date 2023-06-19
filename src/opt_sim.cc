#include "option.h"
#include "signals.h"
#include "opt_sim.h"
#include <fstream>
#include <iostream>
#include "aux.h"


Simulator::Simulator(BSM & opt, Signal & sig, Linear & lin):option(opt), S(sig), time(lin){

}


void Simulator::run(std::string filename){

    std::fstream fout;
    fout.open(filename, std::ios::out);
    fout << option_csv_header() << std::endl;
    for (size_t i = 0; i < S.length(); i++)
    {
        BSM calc_option(S.data[i], option.gK(), option.gexT(),
        option.gR(), option.gSigma(), option.gQ());
        calc_option.setSimTime(time.data[i]);
        fout << calc_option << std::endl;
    }
    fout.close();
}