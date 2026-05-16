#include "course.h"
#include "vector"
#include "student.h"
using namespace std;

class ElectivePicker {
    Student student;
    vector<Course> availableElectives;

public:
    ElectivePicker(Student student);
    const vector<Course>& getAvailableElectives();
    Student pickElective(const string& courseId, const CourseTime& time);

private:
    void findAvailableElectives();
};
