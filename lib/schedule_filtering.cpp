    #include "schedule_filtering.h"
    #include "permutations_generator.h"
    #include <iostream>
    #include <vector>
    using namespace std;

    bool ScheduleFiltering::compareStartTimes(courseTimes x, courseTimes y){return x.start < y.start;}
    double ScheduleFiltering::normalizeDaysOff(double min, double max, double num){
    if (max == min) return 1.0;
    return ((num - min)/(max - min));
    }
    double ScheduleFiltering::normalizeClassesPerDay(double min, double max, double num){
    if (max == min) return 1.0;
    return (1 - (num - min)/(max - min));
    }
    double ScheduleFiltering::normalizeGapHours(double min, double max, double num){
    if (max == min) return 1.0;
    return (1 - (num - min)/(max - min));
    }
    void ScheduleFiltering::scorePermutations(const vector <Course>& courses){
        PermutationsGenerator coursesData(courses);
        nonScoredSchedules = coursesData.conflictResolver(courses);
        if (nonScoredSchedules.empty()) {return;}

        for (const auto& schedule: nonScoredSchedules){
            scheduleScore currentSchedule;
            currentSchedule.earlyMorning = false;
            bool days[5] = {true, true, true, true, true};
            int countForDaysOff = 0;
            vector <courseTimes> arrayForGapHours[5];
            int countForGapHours = 0;
            int maxClasses = 0;

            for (size_t i = 0; i < schedule.size(); i++){
                auto selectedCourseDay = courses[i].getAvailableTimes()[schedule[i]].day;
                auto selectedCourseTime = courses[i].getAvailableTimes()[schedule[i]].startTime;

                // Times of courses in each day
                courseTimes currentTimes;
                currentTimes.start = selectedCourseTime;
                currentTimes.end = selectedCourseTime + courses[i].getDuration();
                arrayForGapHours[selectedCourseDay].push_back(currentTimes);
                
                // Days Off Calculation
                days[selectedCourseDay] = false;
                if (selectedCourseTime < 10){currentSchedule.earlyMorning = true;}
            }
        
            for (const auto& day: days){
                if (day == true){++countForDaysOff;}
            }
            // Gap Hours and Max Classes Per Day calculations
            for(int x = 0; x < 5; x++){
                const auto& day = arrayForGapHours[x];
                if (day.size() > 1) {
                    sort(arrayForGapHours[x].begin(), arrayForGapHours[x].end(), compareStartTimes);
                    for(size_t j = 0; j < day.size()-1; j++){
                        countForGapHours += (day[j+1].start - day[j].end);
                    }
                }
                if (int(day.size()) > maxClasses) {maxClasses = day.size();}
            }
            currentSchedule.daysOff = countForDaysOff;
            currentSchedule.gapHours = countForGapHours;
            currentSchedule.classesInOneDay = maxClasses; 
            scoredSchedules.push_back(currentSchedule);
        }
    }
    void ScheduleFiltering::normalizeValues()
    {
    int maxClassesInADay = 0;
    int minClassesInADay = 990;
    int maxDaysOff = 0;
    int minDaysOff = 990;
    int maxGaps = 0;
    int minGaps = 990;

    for (size_t i = 0; i < scoredSchedules.size(); i++){    
        if (scoredSchedules[i].daysOff > maxDaysOff){maxDaysOff = scoredSchedules[i].daysOff;}
        if (scoredSchedules[i].daysOff < minDaysOff){minDaysOff = scoredSchedules[i].daysOff;}
        if (scoredSchedules[i].classesInOneDay > maxClassesInADay){maxClassesInADay = scoredSchedules[i].classesInOneDay;}
        if (scoredSchedules[i].classesInOneDay < minClassesInADay){minClassesInADay = scoredSchedules[i].classesInOneDay;}
        if (scoredSchedules[i].gapHours > maxGaps){maxGaps = scoredSchedules[i].gapHours;}
        if (scoredSchedules[i].gapHours < minGaps){minGaps = scoredSchedules[i].gapHours;}
    }
    for (size_t i = 0; i < scoredSchedules.size(); i++){
        scoredSchedules[i].normDaysOff = normalizeDaysOff(minDaysOff, maxDaysOff, scoredSchedules[i].daysOff);
        scoredSchedules[i].normClassesInOneDay = normalizeClassesPerDay(minClassesInADay, maxClassesInADay, scoredSchedules[i].classesInOneDay);
        scoredSchedules[i].normGapHours = normalizeGapHours(minGaps, maxGaps, scoredSchedules[i].gapHours);
    }
    }

    void ScheduleFiltering::calculateFinalSchedules()
    {
    int maxBalancedIndex = 0; int maxDaysOffIndex = 0; int maxLateMorningIndex = 0; int maxZeroGapsIndex = 0;
    double maxBalancedScore = 0; double maxDaysOffScore = 0; double maxLateMorningScore = 0; double maxZeroGapsScore = 0;

    for (size_t i = 0; i < scoredSchedules.size(); i++){
    const auto& currentScoredSchedule = scoredSchedules[i];
    double currentDaysOffScore = (3 * currentScoredSchedule.normDaysOff) + double(!currentScoredSchedule.earlyMorning) + currentScoredSchedule.normClassesInOneDay + currentScoredSchedule.normGapHours;
    double currentBalancedScore = (3 * currentScoredSchedule.normClassesInOneDay) + double(!currentScoredSchedule.earlyMorning) + currentScoredSchedule.normDaysOff + currentScoredSchedule.normGapHours;
    double currentLateMorningScore = double(3 * !currentScoredSchedule.earlyMorning) + currentScoredSchedule.normDaysOff + currentScoredSchedule.normClassesInOneDay + currentScoredSchedule.normGapHours;
    double currentZeroGapsScore = (3 * currentScoredSchedule.normGapHours) + double(!currentScoredSchedule.earlyMorning) + currentScoredSchedule.normClassesInOneDay + currentScoredSchedule.normDaysOff;

    if (currentDaysOffScore > maxDaysOffScore) {maxDaysOffScore = currentDaysOffScore; maxDaysOffIndex = i;}
    if (currentBalancedScore > maxBalancedScore) {maxBalancedScore = currentBalancedScore; maxBalancedIndex =i;}
    if (currentLateMorningScore > maxLateMorningScore) {maxLateMorningScore = currentLateMorningScore; maxLateMorningIndex = i;}
    if (currentZeroGapsScore > maxZeroGapsScore) {maxZeroGapsScore = currentZeroGapsScore; maxZeroGapsIndex = i;}
    }

    finalScheduleIndexes.push_back(maxDaysOffIndex); 
    finalScheduleIndexes.push_back(maxBalancedIndex); 
    finalScheduleIndexes.push_back(maxLateMorningIndex); 
    finalScheduleIndexes.push_back(maxZeroGapsIndex);
    }

    void ScheduleFiltering::schedulesToObjects(const vector <Course>& courses){
        scoredSchedules.clear();
        finalScheduleIndexes.clear();
        finalSchedules.clear(); 
        
        scorePermutations(courses);
        if (nonScoredSchedules.empty()) {return;}
        normalizeValues();
        calculateFinalSchedules();
        

        for (int i = 0; i < 4; i++){
            vector <CourseWithSelectedTime> finalCourses;        
            int currentScheduleIndex = finalScheduleIndexes[i];
            const auto& currentSchedule = nonScoredSchedules[currentScheduleIndex];

            for (size_t j = 0; j < currentSchedule.size(); j++){
                const auto& courseTime = courses[j].getAvailableTimes()[currentSchedule[j]];          
                finalCourses.push_back(CourseWithSelectedTime(courses[j], courseTime));
            }

            finalSchedules.push_back(Schedule(finalCourses));
        }
    }

    const vector <Schedule>& ScheduleFiltering::getFinalSchedules(const vector <Course>& courses){
        if (courses.empty()) {return;}
        schedulesToObjects(courses);
        return finalSchedules;
    }