# ZeReSy: The Zewailian Registration System

The University of Science and Technology at Zewail City has a unique system for registering courses; instead of allowing any student to register any course available for the semister, students must adhere to one of multiple templates sent to them in advance. Students are allowed minimal modifications over that template. However, the system the university uses does not prevent students from registering courses that don't adhere to the template. This causes multiple problems:

1. Students require increased concentration, as registering the wrong course may put them on hold. Accendents, even with good intentions, might sabotage a students' entire semister.
2. Registerar employees must review all registrations to check if they follow the tenplates and penlise rogue students.
3. Non-abiding students can cause major delays in the process, as they reserve seats not ment for them, hence preventing other rule-following students from completing their registration.

To solve this problem, we introduce ZeReSy, a registration system purpose built for UST Zewail City and its unique system!

## Project Structure and Build Steps

The project's fiel structure is as follows:

```
ZeReSy/
|
| - include/
| - lib/
| - tests/
| - main.cpp
| - CMakeLists.txt
```

An explanation for each directory/element is listed bellow:

- **include:** the header files for the main components of the program
- **lib:** the implementation (.cpp) files for the program
- **tests:** individual independant tests for deperate parts or functionallities of the program
- **main.cpp:** the entry point fot the application
- **CMakeLists.txt:** cmake file

The program has the following dependancies. Ensure they are on your system before attempting a build.

1. `sqlite3`
2. `libpng`

Use cmake to both build and text (through ctest) the project.

## Contributers
Mohsen Elsisi, Moamen Elkerdany & Youssof Amr.
