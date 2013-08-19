/*
 * FontInformation.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#include "FontInformation.h"
#include <string.h>
#include "GLTexture.h"

FontInformation::FontInformation() :
		fontTexture(NULL), gridPWidth(0), gridPHeight(0), charRight(NULL), charLeft(
				NULL), start(0), end(0) {
}

FontInformation::~FontInformation() {
}

void FontInformation::calculateCharSize(int i) {
	int cID = i - start;
	int cX = (cID % CHARACTER_COUNT_X) * gridPWidth;
	int cY = ((cID / CHARACTER_COUNT_X) * gridPHeight);
	charRight[cID] = 0;
	for (int x = cX + gridPWidth - 1; x >= cX && charRight[cID] == 0; x--) {
		for (int y = cY; y < cY + gridPHeight; y++) {
			GLColor c = fontTexture->getColorAt(x, y); // Icky object allocatation TODO
			if (c.a > 0.0) {
				if (x - cX == gridPHeight - 1) {
					return;
				}
				charRight[cID] = x - cX + 1;
				break;
			}
		}
	}
	charLeft[cID] = 0;
	for (int x = cX; x < cX + charRight[cID] && charRight[cID] != 0; x++) {
		for (int y = cY; y < cY + gridPHeight; y++) {
			GLColor c = fontTexture->getColorAt(x, y); // Icky object allocatation TODO
			if (c.a > 0.0) {
				charLeft[cID] = x - cX - 1;
				return;
			}
		}
	}
	// A totally empty square.  What fun.  Howabouts we eyeball it's size
	charLeft[cID] = gridPWidth / 4;
	charRight[cID] = gridPWidth / 4 * 3;
}

void FontInformation::unloadInternal() {
	if (fontTexture != NULL) {
		fontTexture->freeRawData();
		fontTexture->freeTexture();
		delete fontTexture;
	}
	if (charLeft != NULL) {
		delete[] charLeft;
	}
	if (charRight != NULL) {
		delete[] charRight;
	}
}

bool FontInformation::loadInternal(const char *fileName) {
	if (fontTexture != NULL) {
		return false;
	}

	fontTexture = new GLTexture();
	fontTexture->loadFromFile(fileName);
	start = CHARACTER_OFFSET;
	end = CHARACTER_OFFSET + CHARACTER_COUNT_X * CHARACTER_COUNT_Y;
	gridPWidth = ((float) fontTexture->getWidth())
			/ ((float) CHARACTER_COUNT_X);
	gridPHeight = ((float) fontTexture->getHeight())
			/ ((float) CHARACTER_COUNT_Y);
	if (FONT_MONOSPACED) {
		charRight = NULL;
		charLeft = NULL;
	} else {
		charRight = new float[end - start];
		charLeft = new float[end - start];
		for (register int i = start; i < end; i++) {
			calculateCharSize(i);
		}
	}
	return true;
}

GLTexture *FontInformation::getFontTexture() {
	return fontTexture;
}

void FontInformation::getCharacterInformation(const char c, float &width,
		float &height) {
	int cID = c - start;
	if (c < start || c >= end) {
		width = 0.0;
		height = 0.0;
		return;
	}
	height = gridPHeight;
	if (charRight != NULL && charRight[cID] > 0 && charLeft != NULL) {
		width = charRight[cID] - charLeft[cID];
	} else {
		width = gridPWidth;
	}
}

void FontInformation::getCharacterAddress(const char c, float &cX, float &cY,
		float &cWidth, float &cHeight) {
	int cID = c - start;
	if (c < start || c >= end) {
		cX = 0.0;
		cY = 0.0;
		return;
	}

	cX = (cID % CHARACTER_COUNT_X) * (1.0 / CHARACTER_COUNT_X);
	cY = 1 - ((cID / CHARACTER_COUNT_X) * (1.0 / CHARACTER_COUNT_Y));

	float pixWidth, pixHeight;
	pixHeight = gridPHeight;
	if (charRight != NULL && charRight[cID] > 0 && charLeft != NULL) {
		pixWidth = charRight[cID] - charLeft[cID];
		cX += charLeft[cID] / (float) fontTexture->getWidth();
	} else {
		pixWidth = gridPWidth;
	}

	cWidth = pixWidth / (float) fontTexture->getWidth();
	cHeight = pixHeight / (float) fontTexture->getHeight();
}
