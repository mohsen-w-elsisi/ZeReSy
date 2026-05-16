#include <sqlite3.h>
#include "data_gateway.h"
#include "db_queries.cpp"
#include "utils.cpp"
using namespace std;


// ============= General ===================

DataGateway* DataGateway::i = nullptr;

DataGateway::DataGateway(const string& dbPath) {
    sqlite3_open(dbPath.c_str(), &db);
    execSqlCommand(db, studentQueries::tableCreation);
    execSqlCommand(db, courseQueries::tableCreation);
    execSqlCommand(db, adminQueries::tablecreation);
}

DataGateway::~DataGateway() {
    sqlite3_close(db);
}


// ============ Course Crud ===================

Course parseCourseFromSqliteRow(sqlite3_stmt* stmt);

void DataGateway::setCourse(const Course& course) {
    execSqlCommand(db, courseQueries::set(course));
}

void DataGateway::deleteCourse(const string& courseId) {
    execSqlCommand(db, courseQueries::remove(courseId));
}

Course DataGateway::getCourse(const string& courseId) {
    return getValFromSql<Course>(db, courseQueries::getOne(courseId), courseQueries::parseFrom);
}

vector<Course> DataGateway::getAllCourses() {
    return getManyValsFromSql<Course>(db, courseQueries::getAll, courseQueries::parseFrom);
}



// ============= Student Crud =====================

void DataGateway::setStudent(const Student& student) {
    execSqlCommand(db, studentQueries::set(student));
}

void DataGateway::deleteStudent(int studentId) {
    execSqlCommand(db, studentQueries::remove(studentId));
}

Student DataGateway::getStudent(int studentId) {
    return getValFromSql<Student>(
        db, 
        studentQueries::getOne(studentId), 
        studentQueries::parseFrom
    );
}

vector<Student> DataGateway::getAllStudents() {
    return getManyValsFromSql<Student>(
        db, 
        studentQueries::getAll, 
        studentQueries::parseFrom
    );
}


// ============ Admin CRUD ====================

vector<Admin> DataGateway::getAllAdmins() {
    return getManyValsFromSql<Admin>(
        db,
        adminQueries::getAll,
        adminQueries::parseFrom
    );
}

Admin DataGateway::getAdmin(const string& username) {
    return getValFromSql<Admin>(
        db,
        adminQueries::getOne(username),
        adminQueries::parseFrom
    );
}

void DataGateway::setAdmin(const Admin& admin) {
    execSqlCommand(db, adminQueries::set(admin));
}

void DataGateway::deleteAdmin(const string& username) {
    execSqlCommand(db, adminQueries::remove(username));
}


// =========== DataNotFoundException =============

const char* DataNotFoundException::what() const noexcept {
    return "Did not find entity in database";
}
