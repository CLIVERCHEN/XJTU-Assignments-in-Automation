#include "Free_Line.h"

free_line::free_line() {}

free_line::~free_line() {}

void free_line::draw(QPainter& painter)
{
	painter.setPen(pen);
	for (size_t i = 1; i < free_line_point.size(); i++)
	{
		painter.drawLine(free_line_point[i - 1], free_line_point[i]);
	}
}

void free_line::add_point(QPoint point)
{
	free_line_point.push_back(point);
}