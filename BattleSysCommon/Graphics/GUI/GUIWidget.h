/*
 * GUIWidget.h
 *
 *  Created on: Aug 19, 2013
 *      Author: lwestin
 */

#ifndef GUIWIDGET_H_
#define GUIWIDGET_H_

#include "../../Math/Vector2f.h"

class GUIWidget {
protected:
	bool isHovered;
	bool isFocused;
public:
	Vector2f position;
	Vector2f size;

	GUIWidget();
	virtual ~GUIWidget();
	virtual void render();
	virtual void update(int mouseX, int mouseY);
};

#endif /* GUIWIDGET_H_ */
