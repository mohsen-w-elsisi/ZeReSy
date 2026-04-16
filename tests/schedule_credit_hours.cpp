#include <cassert>
#include "schedule.h"
#include "course.h"
using namespace std;

int main() {
    Course course1(
        "CS100",
        "Introduction to Computer Science And AI",
        3,
        "Dr. Smith",
        {9, 11, 14},
        90,
        false
    );
    Course course2(
        "MATH101",
        "Calculus I",
        2,
        "Dr. Johnson",
        {10, 12, 15},
        90,
        false
    );

    CourseWithSelectedTime cwt1 = course1.selectTime(9);
    CourseWithSelectedTime cwt2 = course2.selectTime(10);

    Schedule schedule({cwt1, cwt2});
    
    assert(schedule.getCreditHours() == 5);
}
