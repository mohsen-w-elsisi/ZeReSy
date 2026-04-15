#include <string>
#include <vector>
using namespace std;

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
    ) : id(id),
        name(name),
        creditHours(creditHours),
        instructorName(instructorName),
        availableTimes(availableTimes),
        duration(duration),
        isElective(isElective) {}

    string getName();
    int getCreditHours();
    string getInstructorName();
    vector<int> getAvailableTimes();
    int getDuration();
    vector<const Course&> getPrerequisites();
    bool getIsElective();
};

class CourseWithSelectedTime : Course {
    int getSelectedTime();
};
