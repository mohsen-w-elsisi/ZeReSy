#pragma once
#include <string>
#include <vector>
using namespace std;

class CourseWithSelectedTime; // Forward declaration for Course::selectTime return type

class Course {
    string id;
    string name;
    int creditHours;
    string instructorName;
    vector<int> availableTimes;
    int duration;
    bool isElective;

public:
    Course(
        string id,
        string name,
        int creditHours,
        string instructorName,
        vector<int> availableTimes,
        int duration,
        bool isElective
    );

    string getId() const;
    string getName() const;
    int getCreditHours() const;
    string getInstructorName() const;
    vector<int> getAvailableTimes() const;
    int getDuration() const;
    vector<const Course*> getPrerequisites() const;
    bool getIsElective() const;
    CourseWithSelectedTime selectTime(int time) const;
};

class CourseWithSelectedTime : public Course {
    int selectedTime;
public:
    CourseWithSelectedTime(Course course, int time);
    int getSelectedTime() const;
};
