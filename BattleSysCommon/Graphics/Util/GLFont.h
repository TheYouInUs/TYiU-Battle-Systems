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
	int start, end;
	int charCountX, charCountY;
	GLTexture fontTexture;
	float gridWidth, gridHeight;
	float gridPWidth, gridPHeight;

	float *charRight;
	float *charLeft;
	void calculateCharSize(int c);
public:
	GLFont(int, int, int, char[], bool);
	void render(char[]);
	virtual ~GLFont();
	void initialize();
	void dispose();
};

#endif /* GLFONT_H_ */
