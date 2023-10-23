#include "Elliptical.h"

elliptical::elliptical() {}

elliptical::~elliptical() {}

void elliptical::draw(QPainter& painter)
{
	painter.setPen(pen);
	painter.drawEllipse(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry());
}

void elliptical::add_point(QPoint point) {}
