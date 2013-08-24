/*
 * GLFont.h
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#ifndef GLFONT_H_
#define GLFONT_H_

class FontInformation;

class GLFont {
private:
	static const float TEXTURE_FONT_SIZE = 32.0;

	float size;
	FontInformation *fontInformation;
public:
	GLFont(FontInformation *fontInformation);
	virtual ~GLFont();

	void setSize(float size);
	float getSize();

	void render(const char *text);

	FontInformation *getFontInformation();
};

#endif /* GLFONT_H_ */
