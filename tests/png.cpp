#include "schedule_exporter.h"

const string TEST_FILENAME = "png_test.png";

int main() {
    remove(TEST_FILENAME.c_str());
    PNG png(300, 900);

    png.fill(255, 127, 0);

    for (int column = 300; column < 600; column++) {
        for (int row = 0; row < 300; row++) {
            png.setPixel(column, row, 255, 0, 0);
        }
    }
    
    png.write(TEST_FILENAME);
}