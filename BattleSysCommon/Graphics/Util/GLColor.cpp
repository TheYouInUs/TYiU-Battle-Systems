/*
 * GLColor.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: westin
 */

#include "GLColor.h"

// RGBA
GLColor::GLColor() {
	r = 1.0;
	g = 1.0;
	b = 1.0;
	a = 1.0;
}

GLColor::~GLColor() {
}

void GLColor::setValue(int value) {
	r = (float) ((value >> 24) & 0xff) / 255.0;
	g = (float) ((value >> 16) & 0xff) / 255.0;
	b = (float) ((value >> 8) & 0xff) / 255.0;
	a = (float) ((value) & 0xff) / 255.0;
}

unsigned int GLColor::getValue() {
	return (((int) (r * 255.0) & 0xff) << 24)
			| (((int) (g * 255.0) & 0xff) << 16)
			| (((int) (b * 255.0) & 0xff) << 8) | (((int) (a * 255.0) & 0xff));
}

