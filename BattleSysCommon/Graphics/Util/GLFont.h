/*
 * GLFont.h
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#ifndef GLFONT_H_
#define GLFONT_H_

#include "GLTexture.h"

class GLFont {
private:
	static const float TEXTURE_FONT_SIZE = 32.0;

	int start, end;
	int charCountX, charCountY;
	GLTexture fontTexture;
	float gridWidth, gridHeight;
	float gridPWidth, gridPHeight;

	float *charRight;
	float *charLeft;
	float size;
	void calculateCharSize(int c);
public:
	GLFont(const char *texName, int offset = 0, int cCountX = 16,
			int cCountY = 16, bool monospace = false);

	void setSize(float size);
	float getSize();

	void render(const char *text);
	virtual ~GLFont();
	void initialize();
	void dispose();
};

#endif /* GLFONT_H_ */
