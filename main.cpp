#include <iostream>
#include <string>
#include "login_ui.h"
using namespace std;

int main() {    
    LoginUI login;

    string id, password;
    
    cout << "enter iD: ";
    cin >> id;
    cout << "enter pass: ";
    cin >> password;

    login.setId(id);
    login.setPass(password);
    login.launchauthenticatedsession();
}
