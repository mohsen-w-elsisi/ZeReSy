#include <cassert>
#include "course.h"
#include "schedule.h"
using namespace std;

const CourseTime mon9{ MON, 9 };
const CourseTime mon10{ MON, 10 };
const CourseTime tue10{ TUE, 10 };

const CourseWithSelectedTime c1 = Course("C1", "Alpha", 3, "ProfA", { mon9 }, 90, false).selectTime(mon9);
const CourseWithSelectedTime c2 = Course("C2", "Beta", 3, "ProfB", { mon10 }, 90, false).selectTime(mon10);
const CourseWithSelectedTime c3 = Course("C3", "Gamma", 3, "ProfC", { mon9 }, 90, false).selectTime(mon9);
const CourseWithSelectedTime c4 = Course("C4", "Delta", 3, "ProfD", { tue10 }, 90, false).selectTime(tue10);
const CourseWithSelectedTime c5 = Course("C5", "theta", 3, "ProfE", { mon9 }, 60, false).selectTime(mon9);

int main() {
    // basic conflic detection
    assert(c1.conflictsWith(c2));
    assert(c2.conflictsWith(c1));
    assert(c1.conflictsWith(c3));
    assert(!c1.conflictsWith(c4));
    assert(!c5.conflictsWith(c2));

    // conflicts while creating schedules
    try {
        Schedule({ c1, c5, c2 });
        return -1;
    }
    catch (SchedulingConflictException e) {}
    Schedule({ c2, c5 });
}