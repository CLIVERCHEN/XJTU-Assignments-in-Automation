#include "Shape.h"

shape::shape() {}

shape::~shape() {}

void shape::set_start_point(QPoint start)
{
	start_point = start;
}

void shape::set_end_point(QPoint end)
{
	end_point = end;
}

void shape::set_pen()
{
	pen.setColor(Qt::black);
	pen.setWidth(1);
}