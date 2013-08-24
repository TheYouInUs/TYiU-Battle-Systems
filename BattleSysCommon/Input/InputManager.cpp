/*
 * InputManager.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: lwestin
 */

#include "InputManager.h"
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdio.h>
#include "../Math/TYIUMath.h"

InputManager *InputManager::instance = NULL;

InputManager *InputManager::get() {
	if (instance == NULL) {
		instance = new InputManager();
	}
	return instance;
}

InputManager::InputManager() :
		initialized(false), currentWindow(NULL), currentKeyBuffer(NULL), previousKeyBuffer(
				NULL), currentMouseButtonBuffer(NULL), previousMouseButtonBuffer(
				NULL), mouseX(0.0), mouseY(0.0) {
}

InputManager::~InputManager() {
	if (initialized) {
		fprintf(stderr, "Input manager deleted before termination!\n");
	}
	if (this == instance) {
		instance = NULL;
	}
}

void InputManager::initialize(GLFWwindow *win) {
	if (initialized) {
		fprintf(stderr, "Input manager already initialized!\n");
		return;
	}
	currentWindow = win;

	currentKeyBuffer = new uint8_t[KEY_BUFFER_SIZE];
	previousKeyBuffer = new uint8_t[KEY_BUFFER_SIZE];
	memset(currentKeyBuffer, 0, sizeof(uint8_t) * KEY_BUFFER_SIZE);
	memset(previousKeyBuffer, 0, sizeof(uint8_t) * KEY_BUFFER_SIZE);

	currentMouseButtonBuffer = new uint8_t[MOUSE_BUTTON_BUFFER_SIZE];
	previousMouseButtonBuffer = new uint8_t[MOUSE_BUTTON_BUFFER_SIZE];
	memset(currentMouseButtonBuffer, 0,
			sizeof(uint8_t) * MOUSE_BUTTON_BUFFER_SIZE);
	memset(previousMouseButtonBuffer, 0,
			sizeof(uint8_t) * MOUSE_BUTTON_BUFFER_SIZE);

	mouseX = 0.0;
	mouseY = 0.0;

	initialized = true;
}

void InputManager::terminate() {
	if (!initialized) {
		fprintf(stderr, "Input manager not initialized!\n");
		return;
	}
	initialized = false;
	currentWindow = NULL;

	delete[] currentKeyBuffer;
	delete[] previousKeyBuffer;

	delete[] currentMouseButtonBuffer;
	delete[] previousMouseButtonBuffer;

	mouseX = 0.0;
	mouseY = 0.0;
}

void InputManager::update() {
	if (!initialized) {
		fprintf(stderr, "Input manager not initialized!\n");
		return;
	}

	// Key Buffers
	memcpy(previousKeyBuffer, currentKeyBuffer,
			sizeof(uint8_t) * KEY_BUFFER_SIZE);
	unsigned register int i = 0;
	for (i = 0; i <= GLFW_KEY_LAST; ++i) {
		setFlag(currentKeyBuffer, i,
				glfwGetKey(currentWindow, i) == GLFW_PRESS);
	}

	// Mouse Position and Buttons
	memcpy(previousMouseButtonBuffer, currentMouseButtonBuffer,
			sizeof(uint8_t) * MOUSE_BUTTON_BUFFER_SIZE);
	glfwGetCursorPos(currentWindow, &mouseX, &mouseY);
	for (i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i) {
		setFlag(currentMouseButtonBuffer, i,
				glfwGetMouseButton(currentWindow, i) == GLFW_PRESS);
	}
}

bool InputManager::isKeyDown(unsigned int key) {
	if (key >= 0 && key <= GLFW_KEY_LAST) {
		return getFlag(currentKeyBuffer, key);
	}
	return false;
}

bool InputManager::isKeyPressed(unsigned int key) {
	if (key >= 0 && key <= GLFW_KEY_LAST) {
		return getFlag(currentKeyBuffer, key)
				&& !getFlag(previousKeyBuffer, key);
	}
	return false;
}

bool InputManager::isMouseDown(unsigned int button) {
	if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST) {
		return getFlag(currentMouseButtonBuffer, button);
	}
	return false;
}

bool InputManager::isMousePressed(unsigned int button) {
	if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST) {
		return getFlag(currentMouseButtonBuffer, button)
				&& !getFlag(previousMouseButtonBuffer, button);
	}
	return false;
}

double InputManager::getMouseX() {
	return mouseX;
}

double InputManager::getMouseY() {
	int width, height;
	glfwGetFramebufferSize(currentWindow, &width, &height);
	return (double) height - mouseY;
}
