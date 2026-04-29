#include <string>
#include <map>

using namespace std;

class LoginUI {
private:
    map<string, string> maps; //dict
    string idinput;
    string passwordInput;

public:
    LoginUI();

    //setters
    void setId(string id);
    void setPass(string pass);

    void launchauthenticatedsession();
};
