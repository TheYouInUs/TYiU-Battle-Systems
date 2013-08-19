/*
 * InputManager.h
 *
 *  Created on: Aug 19, 2013
 *      Author: lwestin
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <stdint.h>
#include <math.h>
#include <GLFW/glfw3.h>

// Takes the ceiling of a float
#define CONST_CEIL(v) ((((v) > (int) (v))) ? (int) (v) + 1 : (int) (v))

class InputManager {
private:
	static const int KEY_BUFFER_SIZE = CONST_CEIL((GLFW_KEY_LAST + 1.0) / 8.0);
	static const int MOUSE_BUTTON_BUFFER_SIZE =
			CONST_CEIL((GLFW_MOUSE_BUTTON_LAST + 1.0) / 8.0);

	static InputManager *instance;

	bool initialized;
	GLFWwindow *currentWindow;
	uint8_t *currentKeyBuffer;
	uint8_t *previousKeyBuffer;

	uint8_t *currentMouseButtonBuffer;
	uint8_t *previousMouseButtonBuffer;
	double mouseX, mouseY;
public:
	static InputManager *get();

	InputManager();
	virtual ~InputManager();

	void initialize(GLFWwindow *window);
	void terminate();
	void update();

	bool isKeyDown(unsigned int key);
	bool isKeyPressed(unsigned int key);

	bool isMouseDown(unsigned int button);
	bool isMousePressed(unsigned int button);

	double getMouseX();
	double getMouseY();
};

#endif /* INPUTMANAGER_H_ */
