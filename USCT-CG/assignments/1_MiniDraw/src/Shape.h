#pragma once
#ifndef SHAPE
#define SHAPE

#include <QPainter>

class shape
{
public:
	shape();
	virtual ~shape();

protected:
	QPoint start_point;
	QPoint end_point;

public:
	virtual void draw(QPainter& painter) = 0;
	virtual void add_point(QPoint point) = 0;

public:
	void set_start_point(QPoint start);
	void set_end_point(QPoint end);

public:
	enum shape_type
	{
		none = 0, 
		line = 1,
		free_line = 2,
		rectangle = 3,
		polygon = 4,
		circle = 5,
		elliptical = 6,
		bezier_curve = 7,
		eraser = 8,
		stepback = 9
	};

public:
	QPen pen;
	void set_pen();
};

#endif // !SHAPE
