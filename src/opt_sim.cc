#include "bsm.h"
#include "signals.h"
#include "opt_sim.h"
#include <fstream>
#include <iostream>
#include "aux.h"

using namespace std;


Simulator::Simulator(BSM<float> * opt, Signal * sig){
    option = opt;
    S = sig;
}


void Simulator::run(string filename){

    std::fstream fout;
    fout.open(filename, ios::out);
    fout << option_csv_header() << endl;
    for (size_t i = 0; i < S->getLength(); i++)
    {
        float tt = (float)i / S->getLength();
        BSM<float> calc_option(S->data[i], option->gK(), option->gexT(),
        option->gR(), option->gSigma(), option->gQ());
        calc_option.setSimTime(tt);
        fout << calc_option << endl;
    }
    fout.close();
}