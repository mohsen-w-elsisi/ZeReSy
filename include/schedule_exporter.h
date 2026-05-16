#pragma once
#include <png.h>
#include "schedule.h"

#define DAYS_COUNT 5
#define HOURS_COUNT 8

#define PIXELS_PER_ROW 50
#define PIXELS_PER_COLUMN 100

#define IMAGE_HEIGHT (HOURS_COUNT*PIXELS_PER_ROW)
#define IMAGE_WIDTH (DAYS_COUNT*PIXELS_PER_COLUMN)

#define BYTES_PER_ROW (IMAGE_WIDTH*3)

class PNG {
    png_struct* pngStr;
    png_info* pngInfo;
    png_byte** pixels;

    int width, height;

public:

    PNG(int height, int width);
    ~PNG();

    void setPixel(int x, int y, int r, int g, int b);
    void fill(int r, int g, int b);
    void write(string filename);
};

class PngPixelOutOfBoundsException : public exception {
public:
    int height, width, pixX, pixY;
    PngPixelOutOfBoundsException(int height, int width, int  pixX, int  pixY);
    const char* what() const noexcept override;
};

class SchedualExporter {
    vector<CourseWithSelectedTime >courses;
    CourseWithSelectedTime* scheduleGrid[DAYS_COUNT][HOURS_COUNT]; // columns first then rows 
    PNG png;
    string filename;

public:
    SchedualExporter(Schedule schedule, const string& filename);
    void exportPNG();

private:
    void addScheduleSlots();
    void addLayout();
};

