#pragma once
#include <string>
#include <sqlite3.h>
#include "course.h"
#include "student.h"
#include "admin.h"
#include "utils.cpp"
using namespace std;

const char STUDENT_TABLE[] = "students";
const char COURESE_TABLE[] = "courses";
const char ADMIN_TABLE[] = "admins";
const char* TABLES[] = { STUDENT_TABLE, COURESE_TABLE, ADMIN_TABLE };

string tableExistanceQuery(string tableName) {
    return "SELECT name FROM sqlite_master WHERE type='table' AND name='"
        + tableName + "'";
}


string encodeAvailableTime(CourseTime time) {
    string dayInidacter = to_string(time.day);
    string timeIndicaor = time.startTime >= 10
        ? to_string(time.startTime)
        : "0" + to_string(time.startTime);
    return dayInidacter + timeIndicaor;
}

CourseTime decodeAvailableTime(string encodedTime) {
    Day day = (Day)stoi(encodedTime.substr(0, 1));
    int time = stoi(encodedTime.substr(1, 2));
    return { day, time };
}

string encodeAvailableTimes(vector<CourseTime> times) {
    string buffer;
    for (const auto& time : times) buffer += encodeAvailableTime(time);
    return buffer;
}

vector<CourseTime> decodeAvailableTimes(string encodedTimes) {
    vector<CourseTime> times;
    for (int i = 0; i < encodedTimes.size() / 3; i += 3) times.push_back(
        decodeAvailableTime(encodedTimes.substr(i, 3))
    );
    return times;
}

string encodeSchedule(const Schedule& schedule) {
    string buffer;
    for (const auto& course : schedule.getCourses()) {
        buffer += course.getId() + encodeAvailableTime(course.getSelectedTime()) + ";";
    }
    return buffer;
}

Schedule decodeSchedule(const string& encodedSchedule, const vector<Course>& allCourses) {
    vector<CourseWithSelectedTime> courses;
    vector<string> courseEntries;

    string currentEntry;
    for (const char c : encodedSchedule) {
        if (c == ';') {
            courseEntries.push_back(currentEntry);
            currentEntry.clear();
        } else {
            currentEntry += c;
        }
    }
    
    for (const auto& entry : courseEntries) {
        string courseId = entry.substr(0, entry.size() - 3);
        string timePart = entry.substr(entry.size() - 3);
        CourseTime selectedTime = decodeAvailableTime(timePart);
        
        Course course("", "", 0, "", {}, 0, false);
        for (const auto& testCourse : allCourses) {
            if (testCourse.getId() == courseId) {
                course = testCourse;
                break;
            }
        }
        if (course.getId().empty()) continue; // course not found, skip

        courses.push_back(course.selectTime(selectedTime));
    }

    return Schedule(courses);
}


namespace courseQueries {
    const string tableCreation =
        "CREATE TABLE IF NOT EXISTS courses ("
        "id TEXT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "credit_hours INT NOT NULL,"
        "instructor_name TEXT NOT NULL,"
        "available_times TEXT NOT NULL,"
        "duration INT NOT NULL,"
        "is_elective BOOLEAN NOT NULL"
        ");";

    const string getAll =
        "SELECT id, name, credit_hours, instructor_name, "
        "available_times, duration, is_elective FROM courses;";

    string getOne(const string& courseId) {
        return "SELECT id, name, credit_hours, instructor_name, "
            "available_times, duration, is_elective FROM courses"
            " WHERE id='" + courseId + "';";
    }

    string set(const Course& course) {
        return "INSERT OR REPLACE INTO courses VALUES ("
            "'" + course.getId() + "',"
            "'" + course.getName() + "'," +
            to_string(course.getCreditHours()) + ","
            "'" + course.getInstructorName() + "',"
            "'" + encodeAvailableTimes(course.getAvailableTimes()) + "'," +
            to_string(course.getDuration()) + "," +
            (course.getIsElective() ? "TRUE" : "FALSE") +
            ");";
    }

    string remove(const string& courseId) {
        return "DELETE FROM courses WHERE id='" + courseId + "';";
    }

    Course parseFrom(sqlite3_stmt* stmt) {
        return Course(
            readTextCol(stmt, 0),
            readTextCol(stmt, 1),
            sqlite3_column_int(stmt, 2),
            readTextCol(stmt, 3),
            decodeAvailableTimes(readTextCol(stmt, 4)),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6) == 1
        );
    }

} // namespace courseQueries


namespace studentQueries {
    const string tableCreation =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "gpa REAL NOT NULL,"
        "completed_courses TEXT NOT NULL,"
        "schedule TEXT,"
        "password BLOB NOT NULL"
        ");";

    const string getAll =
        "SELECT id, name, gpa, completed_courses, schedule, password FROM students";

    string getOne(int studentId) {
        return "SELECT id, name, gpa, completed_courses, schedule, password FROM students "
            " WHERE id=" + to_string(studentId) + ";";
    }

    string set(const Student& student) {
        return "INSERT OR REPLACE INTO students VALUES ("
            + to_string(student.getId()) + ","
            "'" + student.getName() + "'," +
            to_string(student.getGPA()) + ","
            "''," +
            "'" + encodeSchedule(student.getSchedule()) + "'," +
            "'" + student.getPassword() + "'"
            ");";
    }

    string remove(int studentId) {
        return "DELETE FROM students WHERE id=" + to_string(studentId) + ";";
    }

    Student parseFrom(sqlite3_stmt* stmt, const vector<Course>& allCourses) {
        return Student(
            sqlite3_column_int(stmt, 0),
            readTextCol(stmt, 1),
            sqlite3_column_int(stmt, 2),
            {},
            decodeSchedule(readTextCol(stmt, 4), allCourses),
            readTextCol(stmt, 5)
        );
    }
} // namespace studentQueries


namespace adminQueries {
    const char tablecreation[] =
        "CREATE TABLE IF NOT EXISTS admins ("
        "username TEXT PRIMARY KEY,"
        "password TEXT NOT NULL);";

    const char getAll[] = "SELECT username, password FROM admins;";

    string getOne(const string& username) {
        return "SELECT username, password FROM admins "
            "WHERE username='" + username + "';";
    }

    string set(Admin admin) {
        return "INSERT OR REPLACE INTO admins VALUES ("
            "'" + admin.getUsername() + "',"
            "'" + admin.getPassword() + "'"
            ");";
    }

    string remove(const string& username) {
        return "DELETE FROM admins WHERE username='" + username + "';";
    }

    Admin parseFrom(sqlite3_stmt* stmt) {
        return Admin(
            readTextCol(stmt, 0),
            readTextCol(stmt, 1)
        );
    }
} // namespace adminQueries
