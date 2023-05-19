#include <cpr/cpr.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cpr/ssl_options.h>
#include <string.h>

using namespace std;

const string url_indx = "https://api.matbarofex.com.ar/v1/rest/indices/";
const string url_rem = "https://api.remarkets.primary.com.ar/";
const string url_liv = "https://api.primary.com.ar/";
const string auth = "auth/getToken";
const std::vector<std::string> indexs = {"I.CCL", "I.AGTWHEA", "I.AGTKCORA", "I.AGTKSOYA", "I.TRIGO", "I.MAIZ"};
const string credentials_file_name = "credentials.csv";

int get_index()
{

    for (string index : indexs)
    {
        cpr::Response r = cpr::Get(cpr::Url{url_indx + index});
        std::cout << r.text;
    }

    return 0;
}

void get_credentials(vector<string> &cred)

{
    // File pointer
    fstream fin;
    string line, word, temp;

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
};

string get_token(vector<string> &cred)
{
    string url = url_rem + auth;

    cpr::Response r = cpr::Post(cpr::Url{url},
                                cpr::Header{{"X-Username", cred.at(0)},
                                            {"X-Password", cred.at(1)}});
    string token = "";
    if (r.status_code == 200){
        token = r.header["X-Auth-Token"];
    };
    return token;
};

int test_rfx()
{
    vector<string> cred;
    get_credentials(cred);
    string token = get_token(cred);
    cout << token << endl;
    get_index();
    return 0;
}
