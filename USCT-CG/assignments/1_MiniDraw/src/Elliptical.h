#pragma once

#include "Shape.h"
#include <QPainter>

class elliptical :public shape
{
public:
	elliptical();
	~elliptical();

	void draw(QPainter& painter);
	void add_point(QPoint point);
};


