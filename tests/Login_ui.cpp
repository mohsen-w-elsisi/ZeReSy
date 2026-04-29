#include "login_ui.h"
#include <iostream>
using namespace std;

int main()
{
    LoginUI login;
    string id, password;

   
    cout << "enter iD: ";
    cin >> id;
    cout << "enter pass: ";
    cin >> password;

    login.setId(id);
    login.setPass(password);
    login.launchauthenticatedsession();

    return 0;
}