#include <string>
#include <png.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "schedule_exporter.h"
#include "font_size_calculator.cpp"
using namespace std;

class PngTextAnnotater {
    PNG& png;
    string text;

    FT_Library typeLib;
    FT_Face typeFace;

    int fontHeight;

    BoundingBox boundingBox;

    int baseline;
    int penx;
    int peny;

public:
    PngTextAnnotater(PNG& png, string text, BoundingBox boundingBox, int maxFontHeight = -1)
        : png(png),
        text(text),

        boundingBox(boundingBox),
        penx(boundingBox.x) {

        FT_Init_FreeType(&typeLib);
        FT_New_Face(typeLib, FONT_TTF_PATH, 0, &typeFace);

        fontHeight = FontSizeCalulater(text, boundingBox, typeFace).calculatedWidth();
        if (maxFontHeight != -1 && fontHeight > maxFontHeight) fontHeight = maxFontHeight;
        baseline = boundingBox.y + fontHeight;
        FT_Set_Pixel_Sizes(typeFace, 0, fontHeight);
    }

    ~PngTextAnnotater() {
        FT_Done_Face(typeFace);
        FT_Done_FreeType(typeLib);
    }

    void annotate() {
        for (const auto& letter : text) {
            loadGlyph(letter);
            breakLineIfNeeded();
            peny = baseline - typeFace->glyph->bitmap_top;
            writeGlyph();
            penx += typeFace->glyph->advance.x >> 6;
        }
    }

private:
    inline void loadGlyph(const char& letter) {
        int char_index = FT_Get_Char_Index(typeFace, letter);
        FT_Load_Glyph(typeFace, char_index, FT_LOAD_RENDER);
    }

    inline void writeGlyph() {
        for (int row = 0; row < glyphHeight(); row++) {
            for (int col = 0; col < glyphWidth(); col++) {
                int color = glyphColorAt(row, col);
                png.setPixel(penx + col, peny + row, color, color, color);
            }
        }
    }

    inline void breakLineIfNeeded() {
        if (penx + glyphWidth() > boundingBox.x + boundingBox.width) {
            baseline += fontHeight;
            penx = boundingBox.x;
        }
    }

    inline int glyphWidth() { return typeFace->glyph->bitmap.width; }
    inline int glyphHeight() { return typeFace->glyph->bitmap.rows; }
    inline int glyphColorAt(int row, int col) {
        return 255 - typeFace->glyph->bitmap.buffer[row * typeFace->glyph->bitmap.pitch + col];
    }
};
