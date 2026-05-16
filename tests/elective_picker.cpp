#include <vector>
#include <cassert>
#include <iostream>
#include "elective_picker.h"
#include "data_gateway.h"
using namespace std;

const CourseTime mon9{ MON, 9 };
const CourseTime mon11{ MON, 11 };
const CourseTime tue9{ TUE, 9 };
const CourseTime wed13{ WED, 13 };
const CourseTime thu15{ THU, 15 };

const CourseWithSelectedTime c1 = Course("C101", "Math I", 3, "Dr. A", { mon9 }, 3, false).selectTime(mon9);
const CourseWithSelectedTime c2 = Course("C102", "Physics I", 4, "Dr. B", { tue9 }, 2, false).selectTime(tue9);
const CourseWithSelectedTime c3 = Course("C103", "Programming I", 3, "Dr. C", { wed13 }, 2, false).selectTime(wed13);

const CourseWithSelectedTime e1 = Course("E201", "AI Basics", 3, "Dr. D", { mon9 }, 2, true).selectTime(mon9);
const CourseWithSelectedTime e2 = Course("E202", "Digital Art", 2, "Dr. E", { thu15 }, 2, true).selectTime(thu15);

const char TEST_DB_NAME[] = "elective_picker_test.db";

int main() {
    remove(TEST_DB_NAME);
    DataGateway::i = new DataGateway(TEST_DB_NAME);
    DataGateway::i->setCourse(c1);
    DataGateway::i->setCourse(c2);
    DataGateway::i->setCourse(c3);
    DataGateway::i->setCourse(e1);
    DataGateway::i->setCourse(e2);

    Student student(1, "Alice", 3.5, {}, Schedule({ c1, c2, c3 }), "password123");
    ElectivePicker picker(student);

    const vector<Course>& electives = picker.getAvailableElectives();
    cout << electives.size() << endl;
    assert(electives.size() == 1);
    assert(electives[0].getId() == e2.getId());

    student = picker.pickElective(e2.getId(), e2.getSelectedTime());
    assert(student.getSchedule().getCourses().size() == 4);

    bool e2Found = false;
    for (const auto& course : student.getSchedule().getCourses()) {
        if (course.getId() == e2.getId()) e2Found = true;
    }
    assert(e2Found);

    remove(TEST_DB_NAME);
}
