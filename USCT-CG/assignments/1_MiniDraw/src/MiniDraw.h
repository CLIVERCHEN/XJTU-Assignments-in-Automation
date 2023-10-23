#pragma once

#include <QtWidgets/QMainWindow>
#include <QToolButton>
#include "ui_MiniDraw.h"
#include "viewwidget.h"

class MiniDraw : public QMainWindow
{
    Q_OBJECT

public:
    MiniDraw(QWidget *parent = nullptr);
    ~MiniDraw();
    void Init();

private:
    Ui::MiniDrawClass ui;

    QAction* About_Box;

    QAction* Line_action;
    QAction* Free_Line_action;
    QAction* Curve_action;
    QAction* Rectangle_action;
    QAction* Polygon_action;
    QAction* Circle_action;
    QAction* Elliptical_action;
    QAction* Bezier_Curve_action;
    QAction* Eraser_action;
    QAction* StepBack_action;

    QMenu* Menu;

    QToolBar* ToolBar;

private:
    void create_action();
    void create_toolbar();
    void create_menu();
    void AboutBox();

private:
    ViewWidget* view_widget_; // ÉùÃ÷ViewWidgetÖ¸Õë
};
