#include <vector>
#include "course.h"
#include "schedule.h"
using namespace std;

class TemplateGenerator {
    vector<CourseWithSelectedTime> courses;

public:
    TemplateGenerator(vector<CourseWithSelectedTime> courses) : courses(courses) {}

    vector<Schedule> generateTemplates();
    vector <vector<int>> permutationManager();
};