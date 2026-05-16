#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>

using namespace std;

class Authenticator {
public:
    bool login(string id, string pass);
    bool isAdmin(string id);
    bool isStudent(string id);
};

#endif