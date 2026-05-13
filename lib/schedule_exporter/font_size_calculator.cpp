#include <vector>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "bounding_box.cpp"
using namespace std;

#define FONT_TTF_PATH "assets/NotoSans-Regular.ttf"

class FontSizeCalulater {
	string text;
	BoundingBox box;
	FT_Face typeFace;

public:
	FontSizeCalulater(string text, BoundingBox box, FT_Face typeFace)
		:text(text), box(box), typeFace(typeFace) {
	}

	int calculatedWidth() {
		return searchSizes(50, -1);
	}

private:
	int searchSizes(int currentHeight, int lastHeight) {
		int textTotalHeight = calcContainerHeightFor(currentHeight);
		bool textFitsBox = textTotalHeight < box.height;

		if (currentHeight == lastHeight) {
			return textFitsBox
				? currentHeight
				: backtrackUntilValidFontHeight(currentHeight);
		};

		int nextHeight = calcNextTextHeight(currentHeight, lastHeight, textFitsBox);
		return searchSizes(nextHeight, currentHeight);
	}

	inline int calcNextTextHeight(int currentHeight, int lastHeight, bool isSmaller) {
		if (lastHeight == -1) {
			return isSmaller ? currentHeight * 2 : currentHeight / 2;
		}

		int range = currentHeight > lastHeight
			? currentHeight - lastHeight
			: lastHeight - currentHeight;

		return isSmaller
			? currentHeight + range / 2
			: currentHeight - range / 2;
	}

	inline vector<int> calcGlyphWidthsFor(int fontHeight) {
		vector<int> widths(text.length());
		FT_Set_Pixel_Sizes(typeFace, 0, fontHeight);

		for (int i = 0; i < text.length(); i++) {
			int char_index = FT_Get_Char_Index(typeFace, text[i]);
			FT_Load_Glyph(typeFace, char_index, FT_LOAD_RENDER);
			widths[i] = typeFace->glyph->bitmap.width + typeFace->glyph->advance.x >> 6;
		}

		return widths;
	}

	inline int calcContainerHeightFor(int fontHeight) {
		vector<int> widths = calcGlyphWidthsFor(fontHeight);

		int lineCount = 1;
		int currentLineWidth = 0;

		for (const auto width : widths) {
			if (currentLineWidth + width > box.width) {
				lineCount++;
				currentLineWidth = 0;
			}
			currentLineWidth += width;
		}

		return lineCount * fontHeight;
	}

	inline int backtrackUntilValidFontHeight(int height) {
		while (calcContainerHeightFor(height) >= box.height) height--;
		return height;
	}
};
