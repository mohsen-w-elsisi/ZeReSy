#include "application_manager.h"
#include "data_gateway.h"
#include "authenticator.h"
#include "login_ui.h"
#include "student.h"
#include "admin_session.cpp"
#include "student_session.cpp"
using namespace std;


void ApplicationManager::startApplication() {
    initDb();
    loginUser();
}

void ApplicationManager::initDb() {
    DataGateway::i = new DataGateway("zeresy.db");

    DataGateway::i->setStudent(
        Student(1, "John mohamed", 3.5, {}, Schedule({}), "456"));
}

void ApplicationManager::loginUser() {
    Authenticator auth;
    LoginUI loginUI;
    string id, pass;

    while (true) {
        id = loginUI.getId();
        pass = loginUI.getPass();

        try {
            if (auth.login(id, pass)) {
                break;
            }
            else {
                loginUI.invalidPassword();
            }
        }
        catch (DataNotFoundException& e) {
            loginUI.invalidId();
        }
    }

    if (auth.isAdmin(id)) {
        Admin admin = DataGateway::i->getAdmin(id);
        AdminSession(admin).launch();
    }
    else if (auth.isStudent(id)) {
        Student student = DataGateway::i->getStudent(stoi(id.substr(1)));
        StudentSession(student).launch();
    }
}
