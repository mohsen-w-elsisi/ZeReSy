#include "schedule.h"
using namespace std;

class ScheduleLikabilityCalculator{
    Schedule template_;
public:
    double calculateEarlyMorning();
    double calculateMostDaysOff();
    double calculateAfternoon();
};