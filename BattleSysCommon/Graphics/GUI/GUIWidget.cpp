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
		isHovered(false), isFocused(false), position(0, 0), size(0, 0) {
}

GUIWidget::~GUIWidget() {
}

void GUIWidget::update(int mouseX, int mouseY) {
	isHovered = (mouseX >= position.x && mouseY >= position.y
			&& mouseX <= position.x + size.x && mouseY <= position.y + size.y);
	if (InputManager::get()->isMousePressed(GLFW_MOUSE_BUTTON_1)) {
		isFocused = isHovered;
	}
}

void GUIWidget::render() {

}
