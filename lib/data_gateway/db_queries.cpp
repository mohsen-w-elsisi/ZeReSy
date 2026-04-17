#pragma once
#include <string>
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
        "name TEXT,"
        "credit_hours INT," 
        "instructor_name TEXT,"
        "available_times TEXT,"
        "duration INT,"
        "is_elective BOOLEAN"
    ");";       