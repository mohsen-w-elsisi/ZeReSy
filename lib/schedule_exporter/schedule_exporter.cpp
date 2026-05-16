#include <png.h>
#include "schedule_exporter.h"
#include "png.cpp"
#include "png_text_annotater.cpp"
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

            int startRow = hour * PIXELS_PER_ROW;
            int endRow = (hour + course->getDuration() / 60) * PIXELS_PER_ROW;
            int startColumn = day * PIXELS_PER_COLUMN;
            int endColumn = (day + 1) * PIXELS_PER_COLUMN;

            for (int column = startColumn; column < endColumn; column++) {
                for (int row = startRow; row < endRow; row++) {
                    png.setPixel(column, row, 0, 255, 0);
                }
            }

            PngTextAnnotater(
                png, 
                course->getName(), 
                { startColumn, startRow, endColumn - startColumn, endRow - startRow },
                20
            ).annotate();
        }
    }
}