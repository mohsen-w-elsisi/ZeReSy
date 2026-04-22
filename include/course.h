#pragma once
#include <string>
#include <vector>
using namespace std;

class CourseWithSelectedTime; // Forward declaration for Course::selectTime return type

enum Day { SUN, MON, TUE, WED, THU, };

struct CourseTime {
    const Day day;
    const int startTime;
};

class Course {
    string id;
    string name;
    int creditHours;
    string instructorName;
    vector<CourseTime> availableTimes;
    int duration;
    bool isElective;

public:
    Course(
        string id,
        string name,
        int creditHours,
        string instructorName,
        vector<CourseTime> availableTimes,
        int duration,
        bool isElective
    );

    const string& getId() const;
    const string& getName() const;
    int getCreditHours() const;
    const string& getInstructorName() const;
    const vector<CourseTime>& getAvailableTimes() const;
    int getDuration() const;
    vector<const Course*> getPrerequisites() const;
    bool getIsElective() const;
    CourseWithSelectedTime selectTime(CourseTime time) const;
};

class CourseWithSelectedTime : public Course {
    CourseTime selectedTime;
public:
    CourseWithSelectedTime(Course course, CourseTime time);
    CourseTime getSelectedTime() const;
};
 