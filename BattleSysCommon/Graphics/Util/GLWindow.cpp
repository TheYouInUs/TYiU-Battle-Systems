/*
 * GLWindow.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: westin
 */

#include "GLWindow.h"
#include <GL/freeglut.h>

GLWindow::GLWindow(char name[]) {
	handle = glutCreateWindow(name);
}

GLWindow::~GLWindow() {
}

void GLWindow::destroy() {
	glutDestroyWindow(handle);
}

void GLWindow::bind() {
	glutSetWindow(handle);
}

void GLWindow::setVisible(bool visible) {
	bind();
	if (visible) {
		glutShowWindow();
	} else {
		glutHideWindow();
	}
}

void GLWindow::setPosition(int x, int y) {
	bind();
	glutPositionWindow(x, y);
}

void GLWindow::setSize(int w, int h) {
	bind();
	glutReshapeWindow(w, h);
}

void GLWindow::setTitle(char name[]) {
	bind();
	glutSetWindowTitle(name);
}
void GLWindow::setFullscreen(bool fullscreen) {
	bind();
	if (fullscreen != isFullscreen()) {
		glutFullScreenToggle();
	}
}

bool GLWindow::isFullscreen() {
	bind();
	return glutGet(GLUT_FULL_SCREEN);
}
