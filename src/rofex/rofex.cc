#include <cpr/cpr.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
#include "rofex/rofex.h"

using namespace std;

void Token::read_credentials(){
    // File pointer
    fstream fin;
    string line;
    vector<string> cred;

    // Open an existing file
    fin.open(credentials_file_name, ios::in);

    getline(fin, line);
    stringstream s(line);

    std::stringstream sstr(line);
    while (sstr.good())
    {
        std::string substr;
        getline(sstr, substr, ',');
        cred.push_back(substr);
    }

    user = cred.at(0);
    password = cred.at(1);
    cred.clear();
}

string Token::getToken()
{

    std::string url_auth = url_rem + auth;
    cpr::Response r = cpr::Post(cpr::Url{url_auth},
                                cpr::Header{{"X-Username", getUser()},
                                            {"X-Password", getPassword()}});
    string token = "";
    if (r.status_code == 200){

        token = r.header["X-Auth-Token"];
    };

    return token;
}



int get_index()
{

    for (string index : indexs)
    {
        cpr::Response r = cpr::Get(cpr::Url{url_indx + index});
        std::cout << r.text << std::endl;
    }

    return 0;
}

