/*
 * GUIContainer.h
 *
 *  Created on: Aug 22, 2013
 *      Author: lwestin
 */

#ifndef GUICONTAINER_H_
#define GUICONTAINER_H_

#include "GUIWidget.h"
#include <vector>

class GUIContainer: public GUIWidget {
private:
	std::vector<GUIWidget*> children;
public:
	GUIContainer();
	GUIContainer(float x, float y, float width, float height);
	virtual ~GUIContainer();
	void add(GUIWidget* widget);
	virtual void update(double mouseX, double mouseY);
	virtual void render();
	virtual void deepDelete();
};

#endif /* GUICONTAINER_H_ */
