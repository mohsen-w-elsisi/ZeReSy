#include <png.h>
#include "schedule_exporter.h"
using namespace std;

void reportError(png_struct* pngPtr, png_const_charp msg);

SchedualExporter::SchedualExporter(Schedule schedule, const string& filename)
    : courses(schedule.getCourses()) {
    initScheduleGrid();
    initPNGData();
    initFileIO(filename);
    initPixels();
}

void SchedualExporter::initScheduleGrid() {
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

void SchedualExporter::initPNGData() {
    pngStr = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        (png_voidp) nullptr,
        reportError,
        reportError
    );

    pngInfo = png_create_info_struct(pngStr);

    png_set_IHDR(pngStr, pngInfo,
        IMAGE_WIDTH, IMAGE_HEIGHT,  // width and height
        8, PNG_COLOR_TYPE_RGB,      // bit depth (num of bits per channel) and color type (RGB)
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT); //these don't change
}

void SchedualExporter::initFileIO(const string& filename) {
    pngFile = fopen(filename.c_str(), "wb");
    png_init_io(pngStr, pngFile);
}

void SchedualExporter::initPixels() {
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        pixels[i] = new png_byte[BYTES_PER_ROW];
        for (int j = 0; j < BYTES_PER_ROW; j++) {
            pixels[i][j] = 255;
        }
    }
}

SchedualExporter::~SchedualExporter() {
    png_destroy_write_struct(&pngStr, &pngInfo);
    fclose(pngFile);
}

void SchedualExporter::exportPNG() {
    addScheduleSlots();
    png_set_rows(pngStr, pngInfo, pixels);
    png_write_png(pngStr, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);
}

void SchedualExporter::addScheduleSlots() {
    for (int day = 0; day < DAYS_COUNT; day++) {
        for (int hour = 0; hour < HOURS_COUNT; hour++) {
            CourseWithSelectedTime* course = scheduleGrid[day][hour];
            if (course == nullptr) continue;
            for (int column = day * PIXELS_PER_COLUMN; column < (day + 1) * PIXELS_PER_COLUMN; column++) {
                for (int row = hour * PIXELS_PER_ROW; row < (hour + course->getDuration() / 60) * PIXELS_PER_ROW; row++) {
                    pixels[row][column * 3] = 0;
                    pixels[row][column * 3 + 1] = 255;
                    pixels[row][column * 3 + 2] = 0;
                }
            }
        }
    }
}

void reportError(png_struct* pngPtr, png_const_charp msg) { throw exception(); }