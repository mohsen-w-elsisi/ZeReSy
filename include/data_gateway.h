#include <string>
#include <sqlite3.h>
#include "course.h"
#include "student.h"
using namespace std;

class DataGateway {
    sqlite3* db_connection;

public:
    DataGateway(const string& dbPath);
    ~DataGateway();

    vector<Course> getAllCourses();
    Course getCourse(const string& courseId);
    void setCourse(const Course& course);
    void deleteCourse(const string& courseId);

    vector<Student> getAllStudents();
    Student getStudent(int studentId);
    void setStudent(const Student& student);
    void deleteStudent(int studentId);

private:
    void ensure_tables_exist();
};

class DataNotFoundException {
public:
    DataNotFoundException() {}
};