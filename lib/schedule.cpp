#include "schedule.h"
using namespace std;

Schedule::Schedule(vector<CourseWithSelectedTime> courses)
    : courses(courses) {
}

const vector<CourseWithSelectedTime>& Schedule::getCourses() const { return courses; }

int Schedule::getCreditHours() const {
    int total = 0;
    for (const auto& course : courses) {
        total += course.getCreditHours();
    }
    return total;
}
