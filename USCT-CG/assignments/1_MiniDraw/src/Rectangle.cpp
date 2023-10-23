#include "Rectangle.h"

rectangle::rectangle() {}

rectangle::~rectangle() {}

void rectangle::draw(QPainter& painter)
{
	painter.setPen(pen);
	painter.drawRect(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry());
}

void rectangle::add_point(QPoint point) {}