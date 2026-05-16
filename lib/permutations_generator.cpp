// permutation generator
#include "permutations_generator.h"
#include <vector>

vector<vector<int>> PermutationsGenerator::permutationManager(const vector <Course>& courses) {
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
    permutations.push_back(permutation);
    return permutations;
}
void PermutationsGenerator::permutationRecursive(int num, const vector <int> &perms, vector <int> &permu, vector <vector<int>> &final_permutations){
    if (num == perms.size()){final_permutations.push_back(permu); return;}
    for (int i = 0; i < perms[num]; i++){ 
        permu.push_back(i);
        permutationRecursive (num+1, perms, permu, final_permutations);
        permu.pop_back();
    }
}
vector <vector<int>> PermutationsGenerator::conflictResolver(const vector <Course>& courses){
    vector <vector<int>> noConflictPermutations = permutationManager(courses);
    for(size_t i = 0; i < noConflictPermutations.size(); i++){
        bool check = false;
        for (size_t j = 0; j < noConflictPermutations[i].size() - 1; j++){
            if (check) {break;}
            for (size_t k = j+1; k < noConflictPermutations[i].size(); k++){
                const auto& firstCourse = courses[j].getAvailableTimes()[noConflictPermutations[i][j]];
                const auto& secondCourse = courses[k].getAvailableTimes()[noConflictPermutations[i][k]];
                if (firstCourse.day == secondCourse.day && max(secondCourse.startTime, firstCourse.startTime) < min((firstCourse.startTime + courses[j].getDuration()), (secondCourse.startTime + courses[k].getDuration()))){
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