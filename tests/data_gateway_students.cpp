#include <cassert>
#include "data_gateway.h"
using namespace std;

const char TEST_DB_NAME[] = "data_gateway_student_test.db";

const Student MOCK_STUDENT1(202500014, "Mohsen Elsisi", 4, {}, Schedule({}),"123456");
const Student MOCK_STUDENT2(202510262, "Moamen Mohammed", 4, {}, Schedule({}),"123456");
const Student MOCK_STUDENT3(202500014, "Mohsen Waheed", 3.9, {}, Schedule({}),"123456");

int main() {
    // Setup
    remove(TEST_DB_NAME);
    DataGateway* gateway = new DataGateway(TEST_DB_NAME);

    // Create mock courses
    gateway->setStudent(MOCK_STUDENT1);
    gateway->setStudent(MOCK_STUDENT2);

    // Testing getting all courses
    vector<Student> students = gateway->getAllStudents();
    assert(students.size() == 2);

    // Testing querying by courses by id
    Student testStudent = gateway->getStudent(MOCK_STUDENT1.getId());
    assert(testStudent.getName() == MOCK_STUDENT1.getName());

    // Testing deletions
    try {
        gateway->deleteStudent(MOCK_STUDENT2.getId());
        gateway->getStudent(MOCK_STUDENT2.getId());
        return -1;
    }
    catch (const DataNotFoundException& e) {}

    // Testing updates to created Students
    gateway->setStudent(MOCK_STUDENT3);
    testStudent = gateway->getStudent(MOCK_STUDENT1.getId());
    assert(testStudent.getName() == "Mohsen Waheed");

    // Clean up
    delete gateway;
    remove(TEST_DB_NAME);
}
