/*
 * GLFont.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#include "GLFont.h"
#include "GL/gl.h"
#include "FontInformation.h"
#include "GLTexture.h"

GLFont::GLFont(FontInformation *fontInfo) :
		fontInformation(fontInfo) {
	size = TEXTURE_FONT_SIZE;
}

void GLFont::setSize(float f) {
	size = f;
}

float GLFont::getSize() {
	return size;
}

GLFont::~GLFont() {
}

void GLFont::render(const char *text) {
	register int i = 0;
	fontInformation->getFontTexture()->bind();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	float x = 0;

	// Addresses
	float cX, cY, cWidth, cHeight;
	float pixWidth, pixHeight;

	float scale = size / TEXTURE_FONT_SIZE;
	while (text[i] != 0) {
		fontInformation->getCharacterAddress(text[i], cX, cY, cWidth, cHeight);
		fontInformation->getCharacterInformation(text[i], pixWidth, pixHeight);

		glTexCoord2f(cX, cY - cHeight);
		glVertex2f(x * scale, 0);

		glTexCoord2f(cX + cWidth, cY - cHeight);
		glVertex2f((x + pixWidth) * scale, 0);

		glTexCoord2f(cX + cWidth, cY);
		glVertex2f((x + pixWidth) * scale, pixHeight * scale);

		glTexCoord2f(cX, cY);
		glVertex2f(x * scale, pixHeight * scale);

		x += pixWidth;
		++i;
	}
	glEnd();
}

FontInformation *GLFont::getFontInformation() {
	return fontInformation;
}
