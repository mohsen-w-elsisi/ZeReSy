#pragma once
#include <string>
#include <course.h>
#include <student.h>
using namespace std;

const char STUDENT_TABLE[] = "students";
const char COURESE_TABLE[] = "courses";
const char* TABLES[] = { STUDENT_TABLE, COURESE_TABLE };

string tableExistanceQuery(string tableName) {
    return "SELECT name FROM sqlite_master WHERE type='table' AND name='"
        + tableName + "'";
}


//  ================ Course ==========================

const string courseTableCreationStatement =
"CREATE TABLE IF NOT EXISTS courses ("
"id TEXT PRIMARY KEY,"
"name TEXT NOT NULL,"
"credit_hours INT NOT NULL,"
"instructor_name TEXT NOT NULL,"
"available_times TEXT NOT NULL,"
"duration INT NOT NULL,"
"is_elective BOOLEAN NOT NULL"
");";

const string allCoursesQuery =
"SELECT id, name, credit_hours, instructor_name, "
"available_times, duration, is_elective FROM courses;";

string getCourseQuery(const string& courseId) {
    return "SELECT id, name, credit_hours, instructor_name, "
        "available_times, duration, is_elective FROM courses"
        " WHERE id='" + courseId + "';";
}

string createCourseQuery(const Course& course) {
    return "INSERT OR REPLACE INTO courses VALUES ("
        "'" + course.getId() + "'," 
        "'" + course.getName() + "'," +
        to_string(course.getCreditHours()) + "," 
        "'" + course.getInstructorName() + "'," 
        "''," +
        to_string(course.getDuration()) + "," +
        (course.getIsElective() ? "TRUE" : "FALSE") +
        ");";
}

string deleteCourseQuery(const string& courseId) {
    return "DELETE FROM courses WHERE id='" + courseId + "';";
}


//  ================ Student ==========================

const string studentTableCreationStatement = 
"CREATE TABLE students ("
"id INT PRIMARY KEY,"
"name TEXT NOT NULL,"
"gpa REAL NOT NULL,"
"completed_courses TEXT NOT NULL,"
"schedule TEXT,"
"password BLOB"
");";

const string allStudentsQuery = 
"SELECT id, name, gpa, completed_courses, schedule, password FROM students";

string getStudentQuery(int studentId) {
    return "SELECT id, name, gpa, completed_courses, schedule, password FROM students "
        " WHERE id=" + to_string(studentId) + ";";
}

string createStudentQuery(const Student& student) {
    return "INSERT OR REPLACE INTO students VALUES ("
        + to_string(student.getId()) + "," 
        "'" + student.getName() + "'," +
        to_string(student.getGPA()) + "," 
        "''," +
        "''," +
        "'" + student.getPassword() + "'"
        ");";
}

string deleteStudentQuery(int studentId) {
    return "DELETE FROM students WHERE id=" + to_string(studentId) + ";";
}
