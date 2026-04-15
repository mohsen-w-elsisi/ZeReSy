#include <vector>
#include "course.h"
#include "schedule.h"
using namespace std;

class TemplateGenerator {
    vector<Course> courses;

public:
    TemplateGenerator(vector<Course> courses) : courses(courses) {}

    vector<Schedule> generateTemplates();
};