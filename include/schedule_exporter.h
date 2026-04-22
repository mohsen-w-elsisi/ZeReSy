#pragma once
#include <png.h>
#include "schedule.h"

#define DAYS_COUNT 5
#define HOURS_COUNT 12

#define PIXELS_PER_ROW 50
#define PIXELS_PER_COLUMN 100

#define IMAGE_HEIGHT (HOURS_COUNT*PIXELS_PER_ROW)
#define IMAGE_WIDTH (DAYS_COUNT*PIXELS_PER_COLUMN)

#define BYTES_PER_ROW (IMAGE_WIDTH*3)

class SchedualExporter {
    vector<CourseWithSelectedTime >courses;
    CourseWithSelectedTime* scheduleGrid[DAYS_COUNT][HOURS_COUNT]; // columns first then rows 

    png_struct* pngStr;
    png_info* pngInfo;
    FILE* pngFile;
    png_byte* pixels[IMAGE_HEIGHT];

public:
    SchedualExporter(Schedule schedule, const string& filename);
    ~SchedualExporter();
    void exportPNG();

private:
    void initScheduleGrid();
    void initPNGData();
    void initFileIO(const string& filename);
    void initPixels();

    void addScheduleSlots();
    void addLayout();
};
