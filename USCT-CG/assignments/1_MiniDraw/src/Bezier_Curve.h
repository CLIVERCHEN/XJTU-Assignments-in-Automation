#pragma once
#ifndef BEZIER_CURVE
#define BEZIER_CURVE

#include "Shape.h"
#include <QPainter>
#include <vector>
using namespace std;

class bezier_curve :public shape
{
public:
	bezier_curve();
	~bezier_curve();

	vector<QPoint> bezier_curve_control_point;

	void draw(QPainter& painter);
	void add_point(QPoint point);

public:
	double B_coefficient(int n, int i, double t);
	double fact(int n);
};

#endif // !BEZIER_CURVE
