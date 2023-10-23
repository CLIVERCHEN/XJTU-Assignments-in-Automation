#include "viewwidget.h"
#include "./ui_viewwidget.h"
#include <QMouseEvent>
#include <QPainter>

ViewWidget::ViewWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewWidget)
{
    ui->setupUi(this);


    draw_status = false;  // 设置初始状态

    Shape_Type = 0;
}

ViewWidget::~ViewWidget()
{
    delete ui;
}

void ViewWidget::mousePressEvent(QMouseEvent* event)
{
    if (Qt::LeftButton == event->button())
    {
        start_point_ = end_point_ = event->pos();
        switch (Shape_Type)
        {
        case 0:
            break;

        case 1:
            current_shape = new line;
            break;

        case 2:
            current_shape = new free_line;
            break;

        case 3:
            current_shape = new rectangle;
            break;

        case 4:
            if (!draw_status || current_shape == NULL)
            {
                current_shape = new polygon;
                current_shape->add_point(start_point_);
                tmp_point_ = event->pos();
                
            }
            else
            {
                current_shape->add_point(start_point_);
            }
            break;

        case 5:
            current_shape = new circle;
            break;

        case 6:
            current_shape = new elliptical;
            break;

        case 7:
            if (!draw_status || current_shape == NULL)
            {
                current_shape = new bezier_curve;
                current_shape->add_point(start_point_);
                shape_array.push_back(current_shape);
            }
            else
            {
                shape_array.pop_back();
                current_shape->add_point(start_point_);
                shape_array.push_back(current_shape);
            }
            break;

        case 8:
            current_shape = new eraser_;
            break;
        };
        
        draw_status = true;  // 为了判断4，7是否正在画
        if (current_shape != NULL )
        {
            current_shape->set_start_point(start_point_);
            current_shape->set_end_point(end_point_);
        }
    }
    else if (Qt::RightButton == event->button())
    {
        if (Shape_Type == 4)
        {
            current_shape->add_point(tmp_point_);
            shape_array.push_back(current_shape);
            Shape_Type = 0;
        }
    }
}

void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (draw_status && current_shape != NULL)
    {
        end_point_ = event->pos();
        current_shape->set_end_point(end_point_);
        if (Shape_Type == 2 || Shape_Type == 8)
        {
            current_shape->add_point(end_point_);
        }
    }
}

void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (current_shape != NULL && Shape_Type != 4 && Shape_Type != 7)
    {
        current_shape->set_start_point(start_point_);
        current_shape->set_end_point(end_point_);
        shape_array.push_back(current_shape);
        draw_status = false;
    }
}


void ViewWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for (size_t i = 0; i < shape_array.size(); i++)
    {
        shape_array[i]->draw(painter);
    }
    if (current_shape != NULL && Shape_Type != -1)
    {
        current_shape->draw(painter);
    }
    update();
}

void ViewWidget::draw_line()
{
    Shape_Type = 1;
}

void ViewWidget::draw_free_line()
{
    Shape_Type = 2;
}

void ViewWidget::draw_rectangle()
{
    Shape_Type = 3;
}

void ViewWidget::draw_polygon()
{
    Shape_Type = 4;
}

void ViewWidget::draw_circle()
{
    Shape_Type = 5;
}

void ViewWidget::draw_elliptical()
{
    Shape_Type = 6;
}

void ViewWidget::draw_bezier_curve()
{
    Shape_Type = 7;
}

void ViewWidget::eraser()
{
    Shape_Type = 8;
}

void ViewWidget::stepBack()
{
    Shape_Type = -1;
    if (!shape_array.empty())
    {
        shape_array.pop_back();
    }
    if (current_shape != NULL)
    {
        current_shape = NULL;
    }
    draw_status = false;
    update();
}
