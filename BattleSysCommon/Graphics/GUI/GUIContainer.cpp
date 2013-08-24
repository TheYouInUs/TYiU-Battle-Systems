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
	glPopMatrix();
}

void GUIContainer::update(int mouseX, int mouseY) {
	GUIWidget::update(mouseX, mouseY);
	int childX, childY;
	std::vector<GUIWidget*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); ++itr) {
		childX = mouseX + (*itr)->position.x;
		childY = mouseX + (*itr)->position.y;
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
