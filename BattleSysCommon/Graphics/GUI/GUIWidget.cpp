/*
 * GUIWidget.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: lwestin
 */

#include "GUIWidget.h"
#include <GLFW/glfw3.h>
#include "../../Input/InputManager.h"
#include "../Util/FontInformation.h"
#include "../../Resources/ResourceManager.h"

GUIWidget::GUIWidget() :
		hovered(false), hasFocus(false), position(0, 0), size(0, 0) {
	// TODO make this async.  It would be better.  Also the string should be changed
	font = new GLFont(
			ResourceManager::get()->loadSync<FontInformation>("font.png"));
	font->setSize(12.0);
}

GUIWidget::GUIWidget(float x, float y, float width, float height) :
		hovered(false), hasFocus(false), position(x, y), size(width, height) {
	font = new GLFont(
			ResourceManager::get()->loadSync<FontInformation>("font.png"));
	font->setSize(12.0);
}

GUIWidget::~GUIWidget() {
	ResourceManager::get()->destroy(font->getFontInformation());
	delete font;
}

void GUIWidget::update(double mouseX, double mouseY) {
	hovered = (mouseX >= position.x && mouseY >= position.y
			&& mouseX <= position.x + size.x && mouseY <= position.y + size.y);
	if (InputManager::get()->isMousePressed(GLFW_MOUSE_BUTTON_1)) {
		printf("Pressed\n");
		hasFocus = hovered;
	}
}
#if GUI_DEBUG
static char* buffer = new char[50];
#endif

void GUIWidget::render() {
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0);
#if GUI_DEBUG
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(size.x, 0.0);
	glVertex2f(size.x, size.y);
	glVertex2f(0.0, size.y);
	glEnd();
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	sprintf(buffer, "Hovered: %s", hovered ? "true" : "false");
	font->render(buffer);
	sprintf(buffer, "Focused: %s", hasFocus ? "true" : "false");
	glTranslatef(0, font->getSize() + 4.0, 0);
	font->render(buffer);
	glPopMatrix();
#endif
	glPopMatrix();
}

bool GUIWidget::isClicked(unsigned int button) {
	return hovered && InputManager::get()->isMousePressed(button);
}

void GUIWidget::deepDelete() {
	return;
}
