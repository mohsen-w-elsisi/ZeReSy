#pragma once
#include "schedule.h"
#include "permutations_generator.h"
using namespace std;

class ScheduleFiltering{
private:
    vector <vector<int>> nonScoredSchedules;
    struct scheduleScore{
        int daysOff;
        int gapHours;
        bool earlyMorning;
        int classesInOneDay;
        double normDaysOff;
        double normGapHours;
        double normClassesInOneDay;
    };
    struct courseTimes{
        int start;
        int end;
    };
    static bool compareStartTimes(courseTimes x, courseTimes y);
    static double normalizeDaysOff(double min, double max, double num);
    static double normalizeClassesPerDay(double min, double max, double num);
    static double normalizeGapHours(double min, double max, double num);
    void scorePermutations(const vector <Course>& courses);
    void normalizeValues();
    void calculateFinalSchedules();
    vector <scheduleScore> scoredSchedules;
    vector <int> finalScheduleIndexes;
    vector <Schedule> finalSchedules;
    void schedulesToObjects(const vector <Course>& courses);
public:
    const vector <Schedule>& getFinalSchedules(const vector <Course>& courses);
};