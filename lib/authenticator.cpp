#include "authenticator.h"
#include "data_gateway.h"
using namespace std;

bool Authenticator::login(string id, string pass) {
    if (isAdmin(id)) {
        Admin admin = DataGateway::i->getAdmin(id.substr(1));
        if (admin.getPassword() == pass) {
            return true;
        }
        return false;
    } else if (isStudent(id)) {
        Student Student = DataGateway::i->getStudent(stoi(id.substr(1)));
        if (Student.getPassword() == pass) {
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool Authenticator::isAdmin(string id) {
    if (id[0] == 'a') {
        return true;
    }
    return false;
}

bool Authenticator::isStudent(string id) {
    if (id[0] == 's') {
        return true;
    }
    return false;
}