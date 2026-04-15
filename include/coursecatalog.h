#include "course.h"
#include "vector"
using namespace std;

class CourseCatalog {
    vector <Course> courses;
public:
    vector <Course> getElectives();
};