#pragma once
#ifndef LINE
#define LINE

#include <QPainter>
#include "Shape.h"

class line :public shape
{
public:
	line();
	~line();

	void draw(QPainter& painter);
	void add_point(QPoint point);
};

#endif // !LINE
