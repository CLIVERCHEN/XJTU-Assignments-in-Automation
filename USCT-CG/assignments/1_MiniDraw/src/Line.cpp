#include "line.h"

line::line() {}

line::~line() {}

void line::draw(QPainter& painter)
{
	painter.setPen(pen);
	painter.drawLine(start_point, end_point);
}

void line::add_point(QPoint point) {}