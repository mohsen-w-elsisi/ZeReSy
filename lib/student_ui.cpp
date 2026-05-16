#include "student_ui.h"
#include <iostream>
using namespace std;

void StudentUI::displayMenu() {
    cout << "1. View Schedule"<< endl;
    cout << "2. register for schedual"<< endl;
    cout << "3. drop course" << endl;
    cout << "4. register for elective"<< endl;  
    cout << "5. export schedule" << endl;
    cout << "6. logout" << endl;  
}

StudentAction StudentUI::getUserChoice() {
    int action;
    cout << "What would you like to do: ";
    cin >> action;
    return ((StudentAction) action);
}

void StudentUI::displaySchedule(const Schedule& schedule) {
}