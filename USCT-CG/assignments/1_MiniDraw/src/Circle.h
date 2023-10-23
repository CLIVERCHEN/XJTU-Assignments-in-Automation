#pragma once

#include "Shape.h"
#include <QPainter>

class circle :public shape
{
public:
	circle();
	~circle();

	void draw(QPainter& painter);
	void add_point(QPoint point);
};


