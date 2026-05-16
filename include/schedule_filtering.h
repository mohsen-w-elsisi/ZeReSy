#pragma once
#include "schedule.h"
#include "permutations_generator.h"
using namespace std;

class ScheduleLikabilityCalculator{
private:
    TemplateGenerator coursesData;
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
    void scorePermutations();
    void normalizeValues();
    void calculateFinalSchedules();
    vector <scheduleScore> scoredSchedules;
    vector <int> finalScheduleIndexes;
    vector <Schedule> finalSchedules;
public:
    void schedulesToObjects();
    const vector <Schedule>& getFinalSchedules();
};