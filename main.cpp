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
        {9, 11, 14},
        90,
        false
    );
    std::cout << "Course Name: " << course.getName() << "\n";
}
