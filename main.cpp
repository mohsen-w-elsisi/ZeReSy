#include <iostream>
#include "course.h"
using namespace std;

int main(){
    std::cout << "Hello, from ZeReSy!\n";
    Course course(
        "CS101",
        "Introduction to Computer Science",
        3,
        "Dr. Smith",
        { {SUN, 9}, {MON, 11}, {TUE, 14} },
        90,
        false
    );
    std::cout << "Course Name: " << course.getName() << "\n";
}
