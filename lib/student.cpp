#include <student.h>
using namespace std;

Student::Student(
    int id,
    string name,
    int gpa,
    vector<Course> completedCourses,
    Schedule schedule,
    string password
) : id(id),
name(name),
gpa(gpa),
completedCourses(completedCourses),
schedule(schedule),
password(password) {
}

int Student::getId() const { return id; }
string Student::getName() const { return name; }
int Student::getGPA() const { return gpa; }
vector<Course> Student::getCompletedCourses() const { return completedCourses; }
Schedule Student::getSchedule() const { return schedule; }
string Student::getPassword() const { return password; }

int Student::getRegisteredCreditHours()  const {
    return schedule.getCreditHours();
}

// TODO: missing elective picker
