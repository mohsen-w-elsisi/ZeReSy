#include <cassert>
#include "data_gateway.h"
using namespace std;

const char TEST_DB_NAME[] = "data_gateway_admin_test.db";

const Admin MOCK_ADMIN1("admin1", "password1");
const Admin MOCK_ADMIN2("admin2", "password2");
const Admin MOCK_ADMIN3("admin1", "password3");

int main() {
    // Setup
    remove(TEST_DB_NAME);
    DataGateway gateway(TEST_DB_NAME);

    // Create mock admins
    gateway.setAdmin(MOCK_ADMIN1);
    gateway.setAdmin(MOCK_ADMIN2);

    // Testing getting all admins
    vector<Admin> admins = gateway.getAllAdmins();
    assert(admins.size() == 2);

    // Testing querying admins by id
    Admin testAdmin = gateway.getAdmin(MOCK_ADMIN1.getUsername());
    assert(testAdmin.getUsername() == MOCK_ADMIN1.getUsername());
    assert(testAdmin.getPassword() == MOCK_ADMIN1.getPassword());

    // Testing deletions
    try {
        gateway.deleteAdmin(MOCK_ADMIN2.getUsername());
        gateway.getAdmin(MOCK_ADMIN2.getUsername());
        return -1;
    }
    catch (const DataNotFoundException& e) {}

    // Testing updates to created courses
    gateway.setAdmin(MOCK_ADMIN3);
    testAdmin = gateway.getAdmin(MOCK_ADMIN1.getUsername());
    assert(testAdmin.getPassword() == "password3");

    // Clean up
    remove(TEST_DB_NAME);
}

