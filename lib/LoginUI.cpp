#include <iostream>
#include "login_ui.h"

using namespace std;

string LoginUI::getId() {
    string id;
    cout << "Enter ID: ";
    cin >> id;
    return id;
}

string LoginUI::getPass() {
    string pass;
    cout << "Enter Password: ";
    cin >> pass;
    return pass;
}

void LoginUI::invalidId() {
    cout << "Invalid ID. Please try again." << endl;
}

void LoginUI::invalidPassword() {
    cout << "Invalid Password. Please try again." << endl;
}
