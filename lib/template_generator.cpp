#include "/Users/youssof/Desktop/ZeReSy/include/template_generator.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

vector<Schedule> TemplateGenerator::generateTemplates() {
    vector<Schedule> generatedSchedules;
    array<array<string,8>,5> schedule;
    
    for (auto& row : schedule) {
        row.fill("[]");
    }
    
    return generatedSchedules;
}

vector<vector<int>> TemplateGenerator::permutationManager() {
    vector<int> permutation;
    vector<int> perm;
    vector<vector<int>> permutations;
    
    for (const auto& course : courses) {
        permutation.push_back((course.getAvailableTimes().size())-1);
    }
    for (int i = 0; i < permutation.size(); i++) {
        perm.push_back(0);
    }
    
    while (perm != permutation) {
        permutations.push_back(perm);
        int maxIndex = 0;
        bool trigger = false;
        
        for (int i = 0; i < perm.size(); i++) {
            if (perm[i] != permutation[i]) {
                maxIndex = i;
            } else if (perm[i] == permutation[i]) {
                bool check = false;
                trigger = true;
                
                for (int j = (maxIndex + 1); j < perm.size(); j++) {
                    if (perm[j] != permutation[j]) {
                        check = true; 
                        maxIndex = j;
                    }
                }
                
                if (check == false) {
                    fill(perm.begin() + (maxIndex + 1), perm.end(), 0);
                    perm[maxIndex] += 1; 
                    break;
                } else {
                    perm[maxIndex] += 1; 
                    break;
                }
            }
            
            if (trigger == false && i == perm.size()-1) {
                perm[maxIndex] += 1;
            }
        }
    }
    return permutations;
}
void TemplateGenerator::permutationRecursive(int num, const vector <int> &perms, vector <int> &permu, vector <vector<int>> &final_permutations){
    if (num == perms.size()){final_permutations.push_back(permu); return;}
    for (int i = 0; i < perms[num]; i++){ 
        permu.push_back(i);
        permutationRecursive (num+1, perms, permu, final_permutations);
        permu.pop_back();
    }
}
vector <vector<int>> TemplateGenerator::conflictResolver(){
    vector <vector<int>> noConflictPermutations = permutationManager();
    for(int i = 0; i < noConflictPermutations.size(); i++){
        bool check = false;
        for (int j = 0; j < noConflictPermutations[i].size() - 1; j++){
            if (check == true) {break;}
            for (int k = j+1; k < noConflictPermutations[i].size(); k++){
                int firstTime = courses[j].getAvailableTimes()[noConflictPermutations[i][j]].startTime;
                int secondTime = courses[k].getAvailableTimes()[noConflictPermutations[i][k]].startTime;
                int firstDay = courses[j].getAvailableTimes()[noConflictPermutations[i][j]].day;
                int secondDay = courses[k].getAvailableTimes()[noConflictPermutations[i][k]].day;
                if (firstDay == secondDay && abs(secondTime - firstTime) < courses[j].getDuration()){
                    swap(noConflictPermutations[i], noConflictPermutations.back());
                    noConflictPermutations.pop_back();
                    i--;
                    check = true;
                    break;
                }
            }
        }
    }
   return noConflictPermutations; 
}