#include <png.h>
#include "schedule_exporter.h"
#include "png.cpp"
using namespace std;

void reportError(png_struct* pngPtr, png_const_charp msg);

SchedualExporter::SchedualExporter(Schedule schedule, const string& filename)
    : courses(schedule.getCourses()),
    filename(filename),
    png(PNG(IMAGE_HEIGHT, IMAGE_WIDTH)) {

    png.fill(255, 255, 255);

    for (int i = 0; i < DAYS_COUNT; i++) {
        for (int j = 0; j < HOURS_COUNT; j++) {
            scheduleGrid[i][j] = nullptr;
        }
    }

    for (int i = 0; i < courses.size(); i++) {
        CourseWithSelectedTime* course = &(courses[i]);
        int day = course->getSelectedTime().day;
        int time = course->getSelectedTime().startTime - 8;
        scheduleGrid[day][time] = course;
    }
}

void SchedualExporter::exportPNG() {
    addScheduleSlots();
    png.write(filename);
}

void SchedualExporter::addScheduleSlots() {
    for (int day = 0; day < DAYS_COUNT; day++) {
        for (int hour = 0; hour < HOURS_COUNT; hour++) {
            CourseWithSelectedTime* course = scheduleGrid[day][hour];
            if (course == nullptr) continue;

            for (int column = day * PIXELS_PER_COLUMN; column < (day + 1) * PIXELS_PER_COLUMN; column++) {
                for (int row = hour * PIXELS_PER_ROW; row < (hour + course->getDuration() / 60) * PIXELS_PER_ROW; row++) {
                    png.setPixel(column, row, 0, 255, 0);
                }
            }
        }
    }
}