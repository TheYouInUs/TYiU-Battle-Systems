/*
 * GLWindow.h
 *
 *  Created on: Aug 8, 2013
 *      Author: westin
 */

#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <GLFW/glfw3.h>

#define GLFW_INIT_WINDOW_WIDTH 500
#define GLFW_INIT_WINDOW_HEIGHT 500

class GLWindow {
private:
	GLFWwindow *handle;
public:
	GLWindow(const char *name, int width = GLFW_INIT_WINDOW_WIDTH, int height = GLFW_INIT_WINDOW_HEIGHT);
	virtual ~GLWindow();
	void bindContext();
	void destroy();
	void setPosition(int, int);
	void setSize(int, int);
	void setTitle(char[]);
	void setVisible(bool);
	bool isFullscreen();
	bool isClosing();
	void getFramebufferSize(int &width, int &height);
	void swapBuffers();
	GLFWwindow *getHandle();
};

#endif /* GLWINDOW_H_ */
