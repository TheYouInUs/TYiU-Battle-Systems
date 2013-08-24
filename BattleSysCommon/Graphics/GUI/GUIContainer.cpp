/*
 * GUIContainer.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: lwestin
 */

#include "GUIContainer.h"
#include <vector>
#include <GL/gl.h>

GUIContainer::GUIContainer() :
		children() {
}

GUIContainer::GUIContainer(float x, float y, float width, float height) :
		GUIWidget(x, y, width, height), children() {
}

GUIContainer::~GUIContainer() {
}

void GUIContainer::add(GUIWidget* widget) {
	children.push_back(widget);
}

void GUIContainer::render() {
	GUIWidget::render();
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	std::vector<GUIWidget*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); ++itr) {
		(*itr)->render();
	}
#if GUI_DEBUG
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	for (itr = children.begin(); itr != children.end(); ++itr) {
		glVertex2f(0.0, 0.0);
		glVertex2f((*itr)->position.x, (*itr)->position.y);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
#endif
	glPopMatrix();
}

void GUIContainer::update(double mouseX, double mouseY) {
	GUIWidget::update(mouseX, mouseY);
	int childX, childY;
	std::vector<GUIWidget*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); ++itr) {
		childX = mouseX - position.x;
		childY = mouseX - position.y;
		(*itr)->update(childX, childY);
	}
}

void GUIContainer::deepDelete() {
	std::vector<GUIWidget*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); ++itr) {
		(*itr)->deepDelete();
		delete (*itr);
	}
}
