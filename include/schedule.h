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
};