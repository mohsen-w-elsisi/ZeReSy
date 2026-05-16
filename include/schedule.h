#pragma once
#include <vector>
#include "course.h"
using namespace std;

class Schedule {
    vector<CourseWithSelectedTime> courses;
public:
    Schedule(vector<CourseWithSelectedTime> courses);

    const vector<CourseWithSelectedTime>& getCourses() const;
    int getCreditHours() const;
    bool conflictsWith(const CourseWithSelectedTime& course) const;
    void addCourse(const CourseWithSelectedTime& course);
};

class SchedulingConflictException : exception {
public:
    const char* what() const noexcept override;
};
