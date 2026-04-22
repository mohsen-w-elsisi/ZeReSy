#include <cassert>
#include "data_gateway.h"
using namespace std;

const char TEST_DB_NAME[] = "data_gateway_courses_test.db";

const Course MOCK_COURSE1("CSAI 100", "Intro to CSAI", 1, "Dr. Khaled", { {SUN, 9}, {MON, 11} }, 60, false);
const Course MOCK_COURSE2("CSAI 101", "Intro to Python", 3, "Dr. Mohamed", { {TUE, 10}, {WED, 12} }, 120, false);
const Course MOCK_COURSE3("CSAI 100", "Intro to CSAI", 1, "Dr. Doaa", { {SUN, 9}, {MON, 11} }, 60, false);

int main() {
    // Setup
    remove(TEST_DB_NAME);
    DataGateway* gateway = new DataGateway(TEST_DB_NAME);

    // Create mock courses
    gateway->setCourse(MOCK_COURSE1);
    gateway->setCourse(MOCK_COURSE2);

    // Testing getting all courses
    vector<Course> courses = gateway->getAllCourses();
    assert(courses.size() == 2);

    // Testing querying by courses by id
    Course testCourse = gateway->getCourse(MOCK_COURSE1.getId());
    assert(testCourse.getName() == MOCK_COURSE1.getName());

    // Testing deletions
    try {
        gateway->deleteCourse(MOCK_COURSE2.getId());
        gateway->getCourse(MOCK_COURSE2.getId());
        return -1;
    }
    catch (const DataNotFoundException& e) {}

    // Testing updates to created courses
    gateway->setCourse(MOCK_COURSE3);
    testCourse = gateway->getCourse(MOCK_COURSE1.getId());
    assert(testCourse.getInstructorName() == "Dr. Doaa");

    // Clean up
    delete gateway;
    remove(TEST_DB_NAME);
}
