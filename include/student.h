#include <string>
#include "schedule.h"
using namespace std;

class Student {
    int id;
    string name;
    int gpa;
    vector<Course> completedCourses;
    Schedule schedule;

public:
    Student(
        int id,
        string name,
        int gpa,
        vector<Course> completedCourses,
        Schedule schedule
    ): id(id),
        name(name),
        gpa(gpa),
        completedCourses(completedCourses),
        schedule(schedule) {}

    string getName();
    int getGPA();
    vector<Course> getCompletedCourses();
    Schedule getSchedule();
    int getRegisteredCreditHours();    

    void pickElective(Course elective);
};