#include <vector>
#include "course.h"
using namespace std;

class Schedule {
    vector<Course> courses;
public:
    Schedule(vector<Course> courses);

    vector<Course> getCourses();
    int getCreditHours();
};