#include <iostream>
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


