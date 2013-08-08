/*
 * GLColor.h
 *
 *  Created on: Aug 8, 2013
 *      Author: westin
 */

#ifndef GLCOLOR_H_
#define GLCOLOR_H_

class GLColor {
private:
public:
	float r, g, b, a;
	GLColor();
	virtual ~GLColor();
	void setValue(int value);
	unsigned int getValue();
};

#endif /* GLCOLOR_H_ */
