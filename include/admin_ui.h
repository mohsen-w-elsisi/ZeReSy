#include "student.h"
#include "course.h"

enum AdminAction {
    add_STUDENTS=1,
    remove_STUDENTS=2,
    add_COURSES=3,
    remove_COURSES=4,
    add_ADMIN=5,
    logut=6
};

class AdminUI{
public:
    void displayMenu();
    AdminAction getUserChoice();
    Student getStudentInfo();
    Course getCourseInfo();
};
