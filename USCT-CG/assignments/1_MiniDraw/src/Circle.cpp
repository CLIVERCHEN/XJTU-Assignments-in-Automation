#include "Circle.h"

circle::circle() {}

circle::~circle() {}

void circle::draw(QPainter& painter)
{
	painter.setPen(pen);
	double radius = pow(pow((start_point.rx() - end_point.rx()), 2) + pow((start_point.ry() - end_point.ry()), 2), 0.5);
	double x = 0.5 * (end_point.rx() + start_point.rx());
	double y = 0.5 * (end_point.ry() + start_point.ry());
	painter.drawEllipse(x - 0.5 * radius, y - 0.5 * radius, radius, radius);
}

void circle::add_point(QPoint point) {}
