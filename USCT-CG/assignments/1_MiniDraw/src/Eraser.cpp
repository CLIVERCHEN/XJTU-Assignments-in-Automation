#include "Eraser.h"
#include <QColor>
#include "./ui_viewwidget.h"

eraser_::eraser_() {}

eraser_::~eraser_() {}

void eraser_::draw(QPainter& painter)
{
	pen.setColor(Qt::white);
	pen.setWidth(10);
	painter.setPen(pen);
	for (size_t i = 1; i < eraser_point.size(); i++)
	{
		painter.drawLine(eraser_point[i - 1], eraser_point[i]);
	}
}

void eraser_::add_point(QPoint point)
{
	eraser_point.push_back(point);
}