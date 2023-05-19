#ifndef ROFEX_H
#define ROFEX_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;
const std::string url_indx = "https://api.matbarofex.com.ar/v1/rest/indices/";
const std::string url_rem = "https://api.remarkets.primary.com.ar/";
const std::string url_liv = "https://api.primary.com.ar/";
const std::string auth = "auth/getToken";
const std::vector<std::string> indexs = {"I.CCL", "I.AGTWHEA", "I.AGTKCORA", "I.AGTKSOYA", "I.TRIGO", "I.MAIZ"};
const std::string credentials_file_name = "credentials.csv";

class Token
{
private:
    vector<string> cred;
    string user, password;
    void read_credentials();

public:
    Token(){read_credentials();}
    string getUser() { return user; };
    string getPassword() { return password; };
    string getToken();
};

int get_index();

#endif