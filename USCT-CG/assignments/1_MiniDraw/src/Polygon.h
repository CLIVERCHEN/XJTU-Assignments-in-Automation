#pragma once

#include "Shape.h"
#include <QPainter>
#include <vector>
using namespace std;

class polygon :public shape
{
public:
	polygon();
	~polygon();

	vector<QPoint> polygon_point;

	void draw(QPainter& painter);
	void add_point(QPoint point);
};