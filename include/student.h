#pragma once
#include <string>
#include "schedule.h"
using namespace std;

class Student {
    int id;
    string name;
    int gpa;
    vector<Course> completedCourses;
    Schedule schedule;
    string password; // Might change datatype depending on how hashing works

public:
    Student(
        int id,
        string name,
        int gpa,
        vector<Course> completedCourses,
        Schedule schedule,
        string password
    );

    int getId() const;
    string getName() const;
    int getGPA() const;
    vector<Course> getCompletedCourses() const;
    Schedule getSchedule() const;
    int getRegisteredCreditHours() const;
    string getPassword() const;

    void pickElective(Course elective);
};