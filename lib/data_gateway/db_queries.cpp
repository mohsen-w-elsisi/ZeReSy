#pragma once
#include <string>
#include <course.h>
using namespace std;

const char STUDENT_TABLE[] = "students";
const char COURESE_TABLE[] = "courses";
const char* TABLES[] = { STUDENT_TABLE, COURESE_TABLE };

string tableExistanceQuery(string tableName) {
    return "SELECT name FROM sqlite_master WHERE type='table' AND name='"
        + tableName + "'";
}

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
