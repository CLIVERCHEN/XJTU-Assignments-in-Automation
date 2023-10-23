#include "Bezier_Curve.h"
#include <cmath>
#include <vector>
using namespace std;

#define delta 0.01

bezier_curve::bezier_curve() {}

bezier_curve::~bezier_curve() {}

void bezier_curve::draw(QPainter& painter)
{
	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(5);
	painter.setPen(pen);
	for (size_t i = 0; i < bezier_curve_control_point.size(); i++)
	{
		painter.drawPoint(bezier_curve_control_point[i]);
	}

	if (bezier_curve_control_point.size() < 2)
	{
		return;
	}

	vector<QPoint> bezier_curve_point;
	for (double t = 0; t <= 1; t += delta)
	{
		QPoint point;
		int n = bezier_curve_control_point.size();
		for (size_t i = 0; i < n; i++)
		{
			point.rx() += B_coefficient(n - 1, i, t) * bezier_curve_control_point[i].rx();
			point.ry() += B_coefficient(n - 1, i, t) * bezier_curve_control_point[i].ry();
		}
		bezier_curve_point.push_back(point);
	}

	pen.setColor(Qt::black);
	pen.setWidth(1);
	painter.setPen(pen);
	for (size_t i = 1; i < bezier_curve_point.size(); i++)
	{
		painter.drawLine(bezier_curve_point[i - 1], bezier_curve_point[i]);
	}
}

double bezier_curve::B_coefficient(int n, int i, double t)
{
	double ans = (fact(n) * pow(t, i) * pow((1 - t), (n - i))) / (fact(i) * fact(n - i));
	return ans;
}

double bezier_curve::fact(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		return n * fact(n - 1);
	}
}

void bezier_curve::add_point(QPoint point)
{
	bezier_curve_control_point.push_back(point);
}