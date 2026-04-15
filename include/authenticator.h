#include <string>
using namespace std;

enum UserType {
    Student,
    Instructor,
};

class Authenticator {
    string username, password;
    int id;
public:
    Authenticator(string s, string p);
    Authenticator(int i, string p);

    bool login();
};