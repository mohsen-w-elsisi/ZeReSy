#include <string>
#include <png.h>
#include "schedule_exporter.h"
using namespace std;

void reportError(png_struct* pngPtr, png_const_charp msg) { throw exception(); }

PNG::PNG(int height, int width) : width(width), height(height) {
    pngStr = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        (png_voidp) nullptr,
        reportError,
        reportError
    );

    pngInfo = png_create_info_struct(pngStr);

    png_set_IHDR(pngStr, pngInfo,
        width, height,               // width and height
        8, PNG_COLOR_TYPE_RGB,       // bit depth (num of bits per channel) and color type (RGB)
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT //these don't change
    );

    pixels = new png_byte * [height];
    for (int i = 0; i < height; i++) {
        pixels[i] = new png_byte[3 * width];
        for (int j = 0; j < width * 3; j++) {
            pixels[i][j] = 0;
        }
    }
}

PNG::~PNG() {
    png_destroy_write_struct(&pngStr, &pngInfo);
    for (int i = 0; i < height; i++) delete[] pixels[i];
    delete[] pixels;
}

void PNG::setPixel(int x, int y, int r, int g, int b) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        throw PngPixelOutOfBoundsException(height, width, x, y);
    }

    pixels[y][x * 3] = r;
    pixels[y][x * 3 + 1] = g;
    pixels[y][x * 3 + 2] = b;
}

void PNG::fill(int r, int g, int b) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setPixel(i, j, r, g, b);
        }
    }
}

void PNG::write(string filename) {
    png_set_rows(pngStr, pngInfo, pixels);
    FILE* file = fopen(filename.c_str(), "wb");
    png_init_io(pngStr, file);
    png_write_png(pngStr, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);
    fclose(file);
}


PngPixelOutOfBoundsException::PngPixelOutOfBoundsException(int height, int width, int  pixX, int  pixY)
    : height(height), width(width), pixX(pixX), pixY(pixY) {
}

const char* PngPixelOutOfBoundsException::what() const noexcept {
    return string("tried to access position (" +
        to_string(pixX) + "," + to_string(pixY) +
        "), which is outside an image of size " +
        to_string(width) + "x" + to_string(height)).c_str();
}
