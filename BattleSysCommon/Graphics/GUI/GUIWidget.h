/*
 * GUIWidget.h
 *
 *  Created on: Aug 19, 2013
 *      Author: lwestin
 */

#ifndef GUIWIDGET_H_
#define GUIWIDGET_H_

#define GUI_DEBUG 1

#include "../../Math/Vector2f.h"
#include "../Util/GLFont.h"

class GUIWidget {
protected:
	bool hovered;
	bool hasFocus;
	GLFont *font;
public:
	Vector2f position;
	Vector2f size;

	GUIWidget();
	GUIWidget(float x, float y, float width, float height);
	virtual ~GUIWidget();
	virtual void render();
	virtual void update(double mouseX, double mouseY);
	virtual void deepDelete();

	bool isClicked(unsigned int button);
//	inline bool isHovered();
//	inline bool isFocused();


	//Inline functions
	inline bool isHovered() {
		return hovered;
	}

	inline bool isFocused() {
		return hasFocus;
	}
};

#endif /* GUIWIDGET_H_ */
