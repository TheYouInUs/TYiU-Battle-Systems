/*
 * GLFont.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#include "GLFont.h"
#include "GL/gl.h"

GLFont::GLFont(int offset, int charCountX, int charCountY, char texFile[],
		float charWidthOverride) :
		start(offset), charCountX(charCountX), charCountY(charCountY), fontTexture() {
	fontTexture.loadFromFile(texFile);
	end = offset + charCountX * charCountY;
	charPHeight = ((float) fontTexture.getHeight()) / ((float) charCountY);
	if (charWidthOverride > 0) {
		charPWidth = charWidthOverride;
		charWidth = charWidthOverride / ((float) fontTexture.getWidth());
	} else {
		charPWidth = ((float) fontTexture.getWidth()) / ((float) charCountX);
		charWidth = 1.0 / ((float) charCountX);
	}
	charHeight = 1.0 / ((float) charCountY);
}

GLFont::~GLFont() {
	fontTexture.freeRawData();
}

void GLFont::initialize() {
	fontTexture.loadToVRAM();
}

void GLFont::dispose() {
	fontTexture.freeTexture();
}

void GLFont::render(char text[]) {
	register int i = 0;
	fontTexture.bind();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	float x = 0;
	while (text[i] != 0) {
		int cID = text[i] - start;
		if (cID < start || cID >= end) {
			cID = 0;
		}
		float cX = (cID % charCountX) * charWidth;
		float cY = 1 - ((cID / charCountX) * charHeight);

		glTexCoord2f(cX, cY - charHeight);
		glVertex2f(x, 0);

		glTexCoord2f(cX + charWidth, cY - charHeight);
		glVertex2f(x + charPWidth, 0);

		glTexCoord2f(cX + charWidth, cY);
		glVertex2f(x + charPWidth, charPHeight);

		glTexCoord2f(cX, cY);
		glVertex2f(x, charPHeight);

		x += charPWidth;
		++i;
	}
	glEnd();
}
