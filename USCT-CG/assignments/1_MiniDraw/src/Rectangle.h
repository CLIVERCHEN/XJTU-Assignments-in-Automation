#pragma once
#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"
#include <QPainter>

class rectangle :public shape
{
public:
	rectangle();
	~rectangle();

	void draw(QPainter& painter);
	void add_point(QPoint point);
};

#endif // !RECTANGLE
