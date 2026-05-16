#include <iostream>
#include "admin_ui.h"
#include "student.h"
#include "course.h"
using namespace std;

void AdminUI::displayMenu() {
    cout << "Admin Menu:" << endl;
    cout << "1. Add Students" << endl;
    cout << "2. Remove Students" << endl;
    cout << "3. Add Courses" << endl;
    cout << "4. Remove Courses" << endl;
    cout << "5. Add Admin" << endl;
    cout << "6. Logout" << endl;
}

AdminAction AdminUI::getUserChoice() {
    int action;
    cout << "What would you like to do: ";
    cin >> action;
    return ((AdminAction) action);
}

Student AdminUI::getStudentInfo() {
    string id;
    string name;
    string pass;
    
    while (true) {
        cout << "Enter student ID: ";
        cin >> id;
        if(id[0] == 's' || id[0] == 'S'){
            for (char c : id.substr(1)) {
                if (!isdigit(c)) {
                    cout << "Invalid ID. ID should start with 's' followed by digits." << endl;
                    break;
                }
            }
        } else {
            cout << "Invalid ID. ID should start with 's'" << endl;
        }
    }
    
    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student password: ";
    cin >> pass;

    
    return Student(
        stoi(id.substr(1)), 
        name, 
        0, 
        {}, 
        Schedule({}), 
        pass
    );
}

Course AdminUI::getCourseInfo() {
    string id;
    string name;
    string instructorName;
    int creditHours;
    int duratioin; 
    bool isElective;

    cout << "Enter course ID: ";
    cin>> id;
    cout << "Enter course name: ";
    cin >> name;
    cout << "Enter instructor name: ";
    cin >> instructorName;
    cout << "Enter credit hours: ";
    cin >> creditHours;
    cout << "Enter course duration: ";
    cin >> duratioin;
    cout << "Is this course an elective (True or False): ";
    cin >> isElective;

    vector<CourseTime> availableTimes;
    do {
        int startTIme;
        while (true) {
            cout << "Enter course start time (8-16): ";
            cin >> startTIme;
            if (startTIme < 8 || startTIme > 16) {
                cout << "Invalid start time. Please enter a value between 8 and 16." << endl;
            } else {
                break;
            }
        }

        int day;
        while (true) {
            cout << "Enter day : "<<endl 
                 << "1. Sunday" << endl
                 << "2. Monday" << endl
                 << "3. Tuesday" << endl
                 << "4. Wednesday" << endl
                 << "5. Thursday" << endl;
            cin >> day;
            if (day < 1 || day > 5) {
                cout << "Invalid day. Please enter a 1, 2, 3, 4 or 5." << endl;
            } else {
                break;
            }
        }

        CourseTime courseTime = {(Day) (day-1), startTIme};
        availableTimes.push_back(courseTime);
    } while (true);
    
    return Course(id, name, creditHours, instructorName, availableTimes, duratioin, isElective);
} 
