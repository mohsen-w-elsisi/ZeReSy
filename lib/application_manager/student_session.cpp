#include "student_ui.h"
#include "student.h"

class StudentSession {
    Student student;
    StudentUI ui;

public:
    StudentSession(Student student) 
        : student(student), ui(StudentUI()) {
    }

    void launch() {
        while (true) {
            ui.displayMenu();
            StudentAction action = ui.getUserChoice();
            bool shouldQuit = processAction(action);            
            if (shouldQuit) break;
        }
    }

private:
    bool processAction(StudentAction action) {
        switch (action) {
            case StudentAction::VIEW_SCHEDULE:
                break;
            case StudentAction::REGISTER_FOR_SCHEDULE:
                break;
            case StudentAction::DROP_COURSE:
                break;
            case StudentAction::REGISTER_FOR_ELECTIVE:
                break;
            case StudentAction::EXPORT_SCHEDULE:
                break;
            case StudentAction::LOGOUT:
                return true;
        }
        return false;
    }
};
