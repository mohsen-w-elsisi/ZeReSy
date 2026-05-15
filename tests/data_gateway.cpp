#include <cassert>
#include <string>
#include <sqlite3.h>
#include "data_gateway.h"
using namespace std;

const char TEST_DB_NAME[] = "data_gateway_test.db";

bool tableExists(sqlite3* db, const string& name);

int main() {
    remove(TEST_DB_NAME);
    sqlite3* db = nullptr;
    sqlite3_open(TEST_DB_NAME, &db);
    sqlite3_close(db);

    DataGateway* gateway = new DataGateway(TEST_DB_NAME);
    delete gateway;

    db = nullptr;
    sqlite3_open(TEST_DB_NAME, &db);
    assert(tableExists(db, "courses"));
    assert(tableExists(db, "admins"));
    assert(tableExists(db, "students"));
    sqlite3_close(db);
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