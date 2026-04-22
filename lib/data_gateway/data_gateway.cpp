#include <sqlite3.h>
#include "data_gateway.h"
#include "db_queries.cpp"
#include "table_initialiser.cpp"
#include "utils.cpp"
using namespace std;


// ============= General ===================

DataGateway::DataGateway(const string& dbPath) {
    sqlite3_open(dbPath.c_str(), &db);
    ensureTablesInitalised(db);
}

DataGateway::~DataGateway() {
    sqlite3_close(db);
}


// ============ Course Crud ===================

Course parseCourseFromSqliteRow(sqlite3_stmt* stmt);

void DataGateway::setCourse(const Course& course) {
    execSqlCommand(db, createCourseQuery(course));
}

void DataGateway::deleteCourse(const string& courseId) {
    execSqlCommand(db, deleteCourseQuery(courseId));
}

Course DataGateway::getCourse(const string& courseId) {
    return getValFromSql<Course>(db, getCourseQuery(courseId), parseCourseFromSqliteRow);
}

vector<Course> DataGateway::getAllCourses() {
    return getManyValsFromSql<Course>(db, allCoursesQuery, parseCourseFromSqliteRow);
}

Course parseCourseFromSqliteRow(sqlite3_stmt* stmt) {
    return Course(
        readTextCol(stmt, 0),
        readTextCol(stmt, 1),
        sqlite3_column_int(stmt, 2),
        readTextCol(stmt, 3),
        {}, // TODO: available times
        sqlite3_column_int(stmt, 5),
        sqlite3_column_int(stmt, 6) == 1
    );
}


// ============= Student Crud =====================

Student parseStudentFromSqliteRow(sqlite3_stmt* stmt);

void DataGateway::setStudent(const Student& student) {
    execSqlCommand(db, createStudentQuery(student));
}

void DataGateway::deleteStudent(int studentId) {
    execSqlCommand(db, deleteStudentQuery(studentId));
}

Student DataGateway::getStudent(int studentId) {
    return getValFromSql<Student>(db, getStudentQuery(studentId), parseStudentFromSqliteRow);
}

vector<Student> DataGateway::getAllStudents() {
    return getManyValsFromSql<Student>(db, allStudentsQuery, parseStudentFromSqliteRow);
}

Student parseStudentFromSqliteRow(sqlite3_stmt* stmt) {
    return Student(
        sqlite3_column_int(stmt, 0),
        readTextCol(stmt, 1),
        sqlite3_column_int(stmt, 2),
        {},
        Schedule({}),
        readTextCol(stmt, 5)
    );
}
