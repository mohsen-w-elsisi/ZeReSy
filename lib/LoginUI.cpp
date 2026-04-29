#include <iostream>
#include <string>
#include <map>
#include "login_ui.h"
using namespace std;


LoginUI::LoginUI()
{
    // dict
    maps["s001"] = "pass123";
    maps["s002"] = "hello99";
    maps["a001"] = "admin@1";
    idinput = "";
    passwordInput = "";
}

// setters
void LoginUI::setId(string id) { idinput = id; }
void LoginUI::setPass(string pass) { passwordInput = pass; }

void LoginUI::launchauthenticatedsession()
{
    if (maps.count(idinput) > 0)
    {
        if (maps[idinput] == passwordInput)
        {
            if (idinput[0] == 'a')
            {
                cout << "success: admin ui active." << endl;
            }
            else
            {
                cout << "success: Student ui active." << endl;
            }
        }
        else
        {
            cout << "error: " << passwordInput << " is incorrect for id " << idinput << "." << endl;
        }
    }
    else
    {
        cout << "error: " << idinput << " not found." << endl;
    }
};

