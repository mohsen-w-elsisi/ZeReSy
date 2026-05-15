#pragma once
#include <string>
#include <sqlite3.h>
#include "course.h"
#include "student.h"
#include "admin.h"
using namespace std;

class DataGateway {
    sqlite3* db;

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

    vector<Admin> getAllAdmins();
    Admin getAdmin(const string& username);
    void setAdmin(const Admin& admin);
    void deleteAdmin(const string& username);

private:
    void ensure_tables_exist();
};

class DataNotFoundException : public exception {
public:
    const char* what() const noexcept override;
};  