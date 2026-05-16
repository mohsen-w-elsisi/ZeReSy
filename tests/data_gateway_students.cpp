#include <cassert>
#include "data_gateway.h"
#include "schedule.h"
using namespace std;

const char TEST_DB_NAME[] = "data_gateway_student_test.db";

const Schedule MOCK_SCHEDULE = Schedule({
    Course("CS101", "Intro to Programming", 3, "Dr. Smith",{{Day::SUN, 9}}, 2, false).selectTime({Day::SUN, 9}),
    Course("MATH201", "Calculus II", 4, "Dr. Johnson", {{Day::MON, 10}}, 2, false).selectTime({Day::MON, 10})
});

const Student MOCK_STUDENT1(202500014, "Mohsen Elsisi", 4, {}, MOCK_SCHEDULE, "123456");
const Student MOCK_STUDENT2(202510262, "Moamen Mohammed", 4, {}, Schedule({}), "123456");
const Student MOCK_STUDENT3(202500014, "Mohsen Waheed", 3.9, {}, MOCK_SCHEDULE, "123456");

int main() {
    // Setup
    remove(TEST_DB_NAME);
    DataGateway* gateway = new DataGateway(TEST_DB_NAME);
    for (const auto& course : MOCK_SCHEDULE.getCourses()) gateway->setCourse(course);

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

    // Test Schedules are properly stored and retrieved
    assert(testStudent.getSchedule().getCourses().size() == 2);
    assert(testStudent.getSchedule().getCourses()[0].getId() == "CS101");
    assert(testStudent.getSchedule().getCourses()[1].getId() == "MATH201");
    
    // Clean up
    delete gateway;
    remove(TEST_DB_NAME);
}
