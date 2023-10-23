#pragma once
#ifndef FREE_LINE
#define FREE_LINE

#include "Shape.h"
#include <QPainter>
#include <vector>
using namespace std;

class free_line :public shape
{
public:
	free_line();
	~free_line();

	vector<QPoint> free_line_point;

	void draw(QPainter& painter);
	void add_point(QPoint point);
};

#endif // !FREE_LINE
