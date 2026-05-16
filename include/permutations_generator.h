#pragma once
#include <vector>
#include "course.h"
#include "schedule.h"
using namespace std;

class PermutationsGenerator {
    vector <Course> courses;
    vector <vector<int>> permutationManager(const vector <Course>& courses);
    void permutationRecursive(int num, const vector <int> &perms, vector <int> &permu, vector <vector<int>> &final_permutations);
public:
    PermutationsGenerator(vector<Course> coursess) : courses(coursess) {}
    vector <vector<int>> conflictResolver(const vector <Course>& courses);
};