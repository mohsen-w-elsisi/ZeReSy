cmake_minimum_required(VERSION 3.10.0)
project(ZeReSy VERSION 10.44.007 LANGUAGES C CXX)


# ========= External Libraaries ==========

find_package(SQLite3 REQUIRED)
find_package(PNG REQUIRED)

function(add_external_libraries target)
    target_link_libraries(${target} PRIVATE SQLite::SQLite3)    
    target_link_libraries(${target} PRIVATE PNG::PNG)    
endfunction()


# ============ Main Executable ============

add_executable(main main.cpp)
target_include_directories(main PRIVATE include)

set(src_files
    lib/student.cpp
    lib/course.cpp
    lib/schedule.cpp
    lib/schedule_exporter.cpp
    lib/data_gateway/data_gateway.cpp
    lib/LoginUI.cpp
)
target_sources(main PRIVATE ${src_files})

add_external_libraries(main)


# ================ Testing ================

enable_testing()

set(tests
    schedule_credit_hours
    schedule_exporter
    data_gateway
    data_gateway_courses
    data_gateway_students
)

foreach(test ${tests})
    add_executable(${test}_test tests/${test}.cpp)
    target_include_directories(${test}_test PRIVATE include)
    target_sources(${test}_test PRIVATE ${src_files})
    add_external_libraries(${test}_test)
    add_test(NAME ${test}_test COMMAND ${test}_test)
endforeach()
