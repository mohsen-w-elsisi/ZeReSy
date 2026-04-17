#include <iostream>
#include <string>
#include <sqlite3.h>
#include "db_queries.cpp"
using namespace std;

void initCourses(sqlite3* db);

void ensureTablesInitalised(sqlite3* db) {
    initCourses(db);
    // initStudents();
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
    sqlite3_finalize(statement);
}

// void initStudents() {}
