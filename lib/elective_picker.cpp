#include "elective_picker.h"
#include "data_gateway.h"

ElectivePicker::ElectivePicker(Student student) : student(student) {
    findAvailableElectives();
}

void ElectivePicker::findAvailableElectives() {
    for (const auto& course : DataGateway::i->getAllCourses()) {
        if (course.getIsElective()) {
            bool isConflicting = true;
            for (const auto& time : course.getAvailableTimes()) {
                CourseWithSelectedTime cwt = course.selectTime(time);
                if (!student.getSchedule().conflictsWith(cwt)) {
                    isConflicting = false;
                    break;
                }
            }
            if (!isConflicting) availableElectives.push_back(course);
        }
    }
}

const vector<Course>& ElectivePicker::getAvailableElectives() { return availableElectives; }

Student ElectivePicker::pickElective(const string& courseId, const CourseTime& time) {
    const Course* elective = nullptr;

    for (const auto& testCourse : availableElectives) {
        if (testCourse.getId() == courseId) elective = &testCourse;
    }
    if (elective == nullptr) throw exception();

    Schedule modifiedSchedule = student.getSchedule();
    modifiedSchedule.addCourse(elective->selectTime(time));
    student.setSchedule(modifiedSchedule);
    return student;
}
 