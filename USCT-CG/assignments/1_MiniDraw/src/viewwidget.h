#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <ui_viewwidget.h>

#include <QWidget>
#include <vector>
#include <QPainter>
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Free_Line.h"
#include "Polygon.h"
#include "Circle.h"
#include "Elliptical.h"
#include "Eraser.h"
#include "Bezier_Curve.h"
#include "Eraser.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class ViewWidget; }
QT_END_NAMESPACE

class ViewWidget : public QWidget
{
    Q_OBJECT

public:
    ViewWidget(QWidget *parent = nullptr);
    ~ViewWidget();

public:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);

private:
    bool draw_status;
    QPoint start_point_;
    QPoint end_point_;
    QPoint tmp_point_;
    int Shape_Type;

public:
    vector<shape*> shape_array;
    shape* current_shape = NULL;

public slots:
    void draw_line();
    void draw_free_line();
    void draw_rectangle();
    void draw_polygon();
    void draw_circle();
    void draw_elliptical();
    void draw_bezier_curve();
    void eraser();
    void stepBack();

private:
    Ui::ViewWidget *ui;
};
#endif // VIEWWIDGET_H
