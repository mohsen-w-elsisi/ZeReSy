#include <string>
#include <functional>
#include <vector>
#include <sqlite3.h>
using namespace std;

inline string readTextCol(sqlite3_stmt* stmt, int i) {
    auto text = sqlite3_column_text(stmt, i);
    return string((const char*)text);
}

void execSqlCommand(sqlite3* db, string command) {
    sqlite3_stmt* stmt;
    sqlite3_prepare(db, command.c_str(), command.length(), &stmt, nullptr);
    int createRes = sqlite3_step(stmt);
    if (createRes != SQLITE_DONE) throw exception();
    sqlite3_finalize(stmt);
}

template <typename T>
T getValFromSql(sqlite3* db, string query, function<T(sqlite3_stmt*)> rowParser) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr);

    int status = sqlite3_step(stmt);

    switch (status) {
    case SQLITE_ROW: {
        T result = rowParser(stmt);
        sqlite3_finalize(stmt);
        return result;
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

template <typename T>
vector<T> getManyValsFromSql(sqlite3* db, string query, function<T(sqlite3_stmt*)> parseRow) {
    vector<T> results;

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr);

    int status = sqlite3_step(stmt);
    while (status == SQLITE_ROW) {
        T result = parseRow(stmt);
        results.push_back(result);
        status = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    if (status != SQLITE_DONE) throw exception();

    return results;
}

