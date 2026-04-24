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
    void permutationRecursive(int num, const vector <int> &perms, vector <int> &permu, vector <vector<int>> &final_permutations);
    vector <vector<int>> conflictResolver();
};