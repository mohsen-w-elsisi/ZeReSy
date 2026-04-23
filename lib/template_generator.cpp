#include <template_generator.h>
#include <iostream>
#include <string>
using namespace std;

class TemplateGenerator {
    vector<CourseWithSelectedTime> courses;
public:
    TemplateGenerator(vector<CourseWithSelectedTime> courses): courses(courses){}
    vector <Schedule> generateTemplate(){
        array<array<string,8>,5> schedule;
        for (auto& row : schedule) {row.fill("[]");}
    }
    vector <vector<int>> permutationManager (){
        vector <int> permutation;
        vector <int> perm;
        vector <vector<int>> permutations;
        for (const auto& course : courses){permutation.push_back(course.getAvailableTimes().size());}
        for (int i = 0; i<permutation.size(); i++){perm.push_back(0);}
        while (perm != permutation){
           int maxIndex = 0;
           bool trigger = false;
           for (int i = 0; i<perm.size(); i++){
            if (perm[i] != permutation[i]) maxIndex = i;// max index = 2
            else if (perm[i] == permutation[i]) {
                bool check = false;
                trigger = true;
                for (int i = (maxIndex+1); i<perm.size(); i++){
                   if (perm[i] != permutation[i]) {check = true; maxIndex = i;}}
                if (check == false) {
                    fill(perm.begin() + (maxIndex+1), perm.end(), 0);
                    perm[maxIndex] += 1; break;
                }
                else {perm[maxIndex]+=1; break;}
                }
            else if (trigger == false){perm[maxIndex]+=1;}
            }
        }
    }// 0 0 0
};