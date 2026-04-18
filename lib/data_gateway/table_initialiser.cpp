#include <iostream>
#include <string>
#include <sqlite3.h>
#include "db_queries.cpp"
using namespace std;

void initCourses(sqlite3* db);
void initStudents(sqlite3* db);


void ensureTablesInitalised(sqlite3* db) {
    initCourses(db);
    initStudents(db);
}

void initCourses(sqlite3* db) {
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(
        db,
        courseTableCreationStatement.c_str(),
        courseTableCreationStatement.size(),
        &statement,
        nullptr
    );
    int resStatus = sqlite3_step(statement);
    if (resStatus != SQLITE_DONE) throw exception();
    sqlite3_finalize(statement);
}

void initStudents(sqlite3* db) {
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(
        db,
        studentTableCreationStatement.c_str(),
        studentTableCreationStatement.size(),
        &statement,
        nullptr
    );
    int resStatus = sqlite3_step(statement);
    if (resStatus != SQLITE_DONE) throw exception();
    sqlite3_finalize(statement);
}
