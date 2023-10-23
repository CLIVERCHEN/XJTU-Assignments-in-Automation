#pragma once
#ifndef ERASER
#define ERASER

#include "Shape.h"
#include <QPainter>
#include <vector>
using namespace std;

class eraser_ :public shape
{
public:
	eraser_();
	~eraser_();

	vector<QPoint> eraser_point;

	void draw(QPainter& painter);
	void add_point(QPoint point);
};

#endif // !ERASER