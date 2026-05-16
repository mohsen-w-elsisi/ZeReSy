#pragma once
#include "schedule.h"

enum StudentAction {
    VIEW_SCHEDULE = 1 ,
    REGISTER_FOR_SCHEDULE = 2,
    DROP_COURSE = 3,
    REGISTER_FOR_ELECTIVE = 4,
    EXPORT_SCHEDULE = 5,
    LOGOUT = 6
};

class StudentUI {
public:
    void displayMenu();
    StudentAction getUserChoice();
    void displaySchedule(const Schedule& schedule);
};
