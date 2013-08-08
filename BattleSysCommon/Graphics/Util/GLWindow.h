/*
 * GLWindow.h
 *
 *  Created on: Aug 8, 2013
 *      Author: westin
 */

#ifndef GLWINDOW_H_
#define GLWINDOW_H_

class GLWindow {
private:
	int handle;
public:
	GLWindow(char[]);
	virtual ~GLWindow();
	void bind();
	void destroy();
	void setPosition(int, int);
	void setSize(int, int);
	void setTitle(char[]);
	void setVisible(bool);
	void setFullscreen(bool);
	bool isFullscreen();
};

#endif /* GLWINDOW_H_ */
