/*
 * FontInformation.h
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#ifndef FONTINFORMATION_H_
#define FONTINFORMATION_H_

#include "../../Resources/Resource.h"

class GLTexture;

class FontInformation: public Resource {
private:
	//Config values
	static const int CHARACTER_COUNT_X = 16;
	static const int CHARACTER_COUNT_Y = 16;
	static const int CHARACTER_OFFSET = 0;
	static const bool FONT_MONOSPACED = false;

	GLTexture *fontTexture;
	float gridPWidth, gridPHeight;
	float *charRight;
	float *charLeft;
	int start, end;

	void calculateCharSize(int character);
public:
	FontInformation();
	virtual ~FontInformation();

	GLTexture *getFontTexture();
	void getCharacterInformation(const char c, float &width,
			float &height);
	void getCharacterAddress(const char c, float &cX, float &cY,
			float &cWidth, float &cHeight);
protected:
	virtual bool load(const char *file);
	virtual void unload();
};

#endif /* FONTSTORAGE_H_ */
