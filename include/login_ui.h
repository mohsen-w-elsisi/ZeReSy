#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <string>
#include "authenticator.h"

using namespace std;

class LoginUI {
public:
    string getId();
    string getPass();
    void invalidId();
    void invalidPassword();
};

#endif