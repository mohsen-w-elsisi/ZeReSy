cmake_minimum_required(VERSION 3.10.0)
project(ZeReSy VERSION 10.44.007 LANGUAGES C CXX)


# ============ Main Executable ============

add_executable(main main.cpp)
target_include_directories(main PRIVATE include)

set(src_files
    lib/course.cpp
    lib/schedule.cpp
)
target_sources(main PRIVATE ${src_files})


# ================ Testing ================

enable_testing()

set(tests
    schedule_credit_hours
)

foreach(test ${tests})
    add_executable(${test}_test tests/${test}.cpp)
    target_include_directories(${test}_test PRIVATE include)
    target_sources(${test}_test PRIVATE ${src_files})
    add_test(NAME ${test}_test COMMAND ${test}_test)
endforeach()

# be kol nashaat! 