#pragma once
#include <string>
using namespace std;

class Admin {
    string username;
    string password;
public:
    Admin(string username, string password)
        : username(username), password(password) {
    }
    
    inline const string& getUsername() const { return username; }
    inline const string& getPassword() const { return password; }
};