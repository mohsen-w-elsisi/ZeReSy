#include <vector>
#include "course.h"
#include "schedule.h"
using namespace std;

class TemplateGenerator {
    vector<Course> courses;

public:
    TemplateGenerator(vector<Course> courses) : courses(courses) {}

    vector <vector<int>> permutationManager();
    void permutationRecursive(int num, const vector <int> &perms, vector <int> &permu, vector <vector<int>> &final_permutations);
    vector <vector<int>> conflictResolver();
};