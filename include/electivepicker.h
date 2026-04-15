#include "course.h"
#include "vector"
#include "student.h"
using namespace std;

class ElectivePicker{
    Course elective;
    Student student;

public:
    ElectivePicker(Course elective, Student student);
    void pickElective();
};
