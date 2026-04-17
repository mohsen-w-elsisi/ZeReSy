#include <cassert>
#include <string>
#include <sqlite3.h>
#include "data_gateway.h"
using namespace std;

const char TEST_DB_NAME[] = "data_gateway_test.db";

void createTable(sqlite3* db, const string& name);
bool tableExists(sqlite3* db, const string& name);

int main() {
    // creates table if not exists
    remove(TEST_DB_NAME);
    sqlite3* db = nullptr;
    sqlite3_open(TEST_DB_NAME, &db);
    sqlite3_close(db);

    DataGateway* gateway = new DataGateway(TEST_DB_NAME);
    delete gateway;

    db = nullptr;
    sqlite3_open(TEST_DB_NAME, &db);
    assert(tableExists(db, "courses"));
    sqlite3_close(db);
}

void createTable(sqlite3* db, const string& name) {
    string statement = "CREATE TABLE " + name + "(id INT);";
    sqlite3_stmt* compiledStatemen = nullptr;
    sqlite3_prepare_v2(db, statement.c_str(), statement.length(), &compiledStatemen, nullptr);
    int resStatus = sqlite3_step(compiledStatemen);
    assert(resStatus == SQLITE_DONE);
    sqlite3_finalize(compiledStatemen);
}

bool tableExists(sqlite3* db, const string& table_name) {
    const string query =
        "SELECT name FROM sqlite_master WHERE type='table' AND name='" + table_name + "';";

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db, query.c_str(), query.size(), &stmt, nullptr);

    const int status = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return status == SQLITE_ROW;
}