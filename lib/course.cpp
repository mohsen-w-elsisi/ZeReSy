#include <string>
#include "course.h"
using namespace std;

Course::Course(
    string id,
    string name,
    int creditHours,
    string instructorName,
    vector<int> availableTimes,
    int duration,
    bool isElective
) : id(id),
name(name),
creditHours(creditHours),
instructorName(instructorName),
availableTimes(availableTimes),
duration(duration),
isElective(isElective) {
}

string Course::getId() const { return id; }
string Course::getName() const { return name; }
int Course::getCreditHours() const { return creditHours; }
string Course::getInstructorName() const { return instructorName; }
vector<int> Course::getAvailableTimes() const { return availableTimes; }
int Course::getDuration() const { return duration; }
bool Course::getIsElective() const { return isElective; }

vector<const Course*> Course::getPrerequisites() const {
    return vector<const Course*>();
}

CourseWithSelectedTime Course::selectTime(int time) const {
    return CourseWithSelectedTime(*this, time);
}

// CourseWithSelectedTime implementation

CourseWithSelectedTime::CourseWithSelectedTime(Course course, int time) :
    Course(course), selectedTime(time) {
}

int CourseWithSelectedTime::getSelectedTime() const { return selectedTime; }

