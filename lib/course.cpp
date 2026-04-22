#include <string>
#include "course.h"
using namespace std;

Course::Course(
    string id,
    string name,
    int creditHours,
    string instructorName,
    vector<CourseTime> availableTimes,
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

const string& Course::getId() const { return id; }
const string& Course::getName() const { return name; }
int Course::getCreditHours() const { return creditHours; }
const string& Course::getInstructorName() const { return instructorName; }
const vector<CourseTime>& Course::getAvailableTimes() const { return availableTimes; }
int Course::getDuration() const { return duration; }
bool Course::getIsElective() const { return isElective; }

vector<const Course*> Course::getPrerequisites() const {
    return vector<const Course*>();
}

CourseWithSelectedTime Course::selectTime(CourseTime time) const {
    return CourseWithSelectedTime(*this, time);
}

// CourseWithSelectedTime implementation

CourseWithSelectedTime::CourseWithSelectedTime(Course course, CourseTime time) :
    Course(course), selectedTime(time) {
}

CourseTime CourseWithSelectedTime::getSelectedTime() const { return selectedTime; }

