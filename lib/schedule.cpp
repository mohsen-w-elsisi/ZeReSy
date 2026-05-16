#include <cmath>
#include "schedule.h"
using namespace std;

Schedule::Schedule(vector<CourseWithSelectedTime> courses) {
    for (const auto& course : courses) {
        if (conflictsWith(course)) throw SchedulingConflictException();
        this->courses.push_back(course);
    }
}

const vector<CourseWithSelectedTime>& Schedule::getCourses() const { return courses; }

int Schedule::getCreditHours() const {
    int total = 0;
    for (const auto& course : courses) {
        total += course.getCreditHours();
    }
    return total;
}

bool Schedule::conflictsWith(const CourseWithSelectedTime& testCourse) const {
    for (const auto& existingCourse : courses) {
        if (existingCourse.conflictsWith(testCourse)) return true;
    }
    return false;
}

void Schedule::addCourse(const CourseWithSelectedTime& course) {
    if (conflictsWith(course)) throw SchedulingConflictException();
    courses.push_back(course);
}


const char* SchedulingConflictException::what() const noexcept {
    return "Scheduling conflict found between courses";
}


