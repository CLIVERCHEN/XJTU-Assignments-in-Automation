#include "Polygon.h"

polygon::polygon() {}

polygon::~polygon() {}

void polygon::draw(QPainter& painter)
{
	painter.setPen(pen);
	for (size_t i = 1; i < polygon_point.size(); i++)
	{
		painter.drawLine(polygon_point[i - 1], polygon_point[i]);
	}
}

void polygon::add_point(QPoint point)
{
	polygon_point.push_back(point);
}