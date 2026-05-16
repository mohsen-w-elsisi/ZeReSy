#include "admin.h"
#include "admin_ui.h"

class AdminSession {
    Admin admin;
    AdminUI ui;

public:
    AdminSession(Admin admin)
        : admin(admin), ui(AdminUI()) {
    }

    void launch() {
    }

private:
    void processAction(AdminAction action) {}
};