#include <sqlite3.h>
#include "data_gateway.h"
#include "db_queries.cpp"
#include "table_initialiser.cpp"
using namespace std;

DataGateway::DataGateway(const string& dbPath) {
    sqlite3_open(dbPath.c_str(), &db_connection);
    ensureTablesInitalised(db_connection);
}

DataGateway::~DataGateway() {
    sqlite3_close(db_connection);
}

Course parseCourseFromSqliteRow(sqlite3_stmt* stmt);
string readTextCol(sqlite3_stmt* stmt, int i);

vector<Course> DataGateway::getAllCourses() {
    vector<Course> courses;

    sqlite3_stmt* statement;
    sqlite3_prepare_v2(
        db_connection, allCoursesQuery.c_str(),
        allCoursesQuery.length(), &statement, nullptr);

    int status = sqlite3_step(statement);
    while (status == SQLITE_ROW) {
        Course course = parseCourseFromSqliteRow(statement);
        courses.push_back(course);
        status = sqlite3_step(statement);
    }

    sqlite3_finalize(statement);
    if (status != SQLITE_DONE) throw exception();

    return courses;
}

Course DataGateway::getCourse(const string& courseId) {
    string query = getCourseQuery(courseId);
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db_connection, query.c_str(), query.length(), &stmt, nullptr);
    int status = sqlite3_step(stmt);

    switch (status) {
    case SQLITE_ROW: {
        Course course = parseCourseFromSqliteRow(stmt);
        sqlite3_finalize(stmt);
        return course;
    }
    case SQLITE_DONE: {
        sqlite3_finalize(stmt);
        throw DataNotFoundException();
    }
    default: {
        sqlite3_finalize(stmt);
        throw exception();
    }
    }
}

Course parseCourseFromSqliteRow(sqlite3_stmt* stmt) {
    return Course(
        readTextCol(stmt, 0),
        readTextCol(stmt, 1),
        sqlite3_column_int(stmt, 2),
        readTextCol(stmt, 3),
        { 0 }, // TODO: available times
        sqlite3_column_int(stmt, 5),
        sqlite3_column_int(stmt, 6) == 1
    );
}

void DataGateway::setCourse(const Course& course) {
    string query = createCourseQuery(course);
    sqlite3_stmt* stmt;
    sqlite3_prepare(db_connection, query.c_str(), query.length(), &stmt, nullptr);
    int createRes = sqlite3_step(stmt);
    if (createRes != SQLITE_DONE) throw exception();
    sqlite3_finalize(stmt);
}

void DataGateway::deleteCourse(const string& courseId) {
    string query = deleteCourseQuery(courseId);
    sqlite3_stmt* stmt;
    sqlite3_prepare(db_connection, query.c_str(), query.length(), &stmt, nullptr);
    int createRes = sqlite3_step(stmt);
    if (createRes != SQLITE_DONE) throw exception();
    sqlite3_finalize(stmt);
}

string readTextCol(sqlite3_stmt* stmt, int i) {
    auto text = sqlite3_column_text(stmt, i);
    return string((const char*)text);
}

