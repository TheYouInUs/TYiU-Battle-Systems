/*
 * GUIWidget.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: lwestin
 */

#include "GUIWidget.h"
#include <GLFW/glfw3.h>
#include "../../Input/InputManager.h"

GUIWidget::GUIWidget() :
		hovered(false), hasFocus(false), position(0, 0), size(0, 0) {
}

GUIWidget::GUIWidget(float x, float y, float width, float height) :
		hovered(false), hasFocus(false), position(x, y), size(width, height) {
}

GUIWidget::~GUIWidget() {
}

void GUIWidget::update(int mouseX, int mouseY) {
	hovered = (mouseX >= position.x && mouseY >= position.y
			&& mouseX <= position.x + size.x && mouseY <= position.y + size.y);
	if (InputManager::get()->isMousePressed(GLFW_MOUSE_BUTTON_1)) {
		hasFocus = hovered;
	}
}

void GUIWidget::render() {
#if GUI_DEBUG
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(position.x, position.y);
	glVertex2f(position.x + size.x, position.y);
	glVertex2f(position.x + size.x, position.y + size.y);
	glVertex2f(position.x, position.y + size.y);
	glEnd();
	glEnable(GL_TEXTURE_2D);
#endif
}

bool GUIWidget::isClicked(unsigned int button) {
	return hovered && InputManager::get()->isMousePressed(button);
}

void GUIWidget::deepDelete() {
	return;
}
