/*
 * GLWindow.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: westin
 */

#include "GLWindow.h"
#include <GLFW/glfw3.h>

GLWindow::GLWindow(const char *name, int width, int height) {
	handle = glfwCreateWindow(width, height, name, NULL, NULL);
}

GLWindow::~GLWindow() {
}

void GLWindow::destroy() {
	glfwDestroyWindow(handle);
}

void GLWindow::bindContext() {
	glfwMakeContextCurrent(handle);
}

void GLWindow::swapBuffers() {
	glfwSwapBuffers(handle);
}

GLFWwindow *GLWindow::getHandle() {
	return handle;
}

void GLWindow::setVisible(bool visible) {
	if (visible) {
		glfwShowWindow(handle);
	} else {
		glfwHideWindow(handle);
	}
}

void GLWindow::setPosition(int x, int y) {
	glfwSetWindowPos(handle, x, y);
}

void GLWindow::setSize(int w, int h) {
	glfwSetWindowSize(handle, w, h);
}

void GLWindow::setTitle(char name[]) {
	glfwSetWindowTitle(handle, name);
}

bool GLWindow::isFullscreen() {
	return glfwGetWindowMonitor(handle) != NULL;
}

bool GLWindow::isClosing() {
	return glfwWindowShouldClose(handle);
}

void GLWindow::getFramebufferSize(int &width, int &height) {
	glfwGetFramebufferSize(handle, &width, &height);
}
