#include "MiniDraw.h"
#include "viewwidget.h"
#include <QToolBar>
#include <QMessageBox>

MiniDraw::MiniDraw(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setAutoFillBackground(true);
    QPalette pa;
    pa.setBrush(this->backgroundRole(), QBrush(Qt::white));
    this->setPalette(pa);

    Init();

    create_action();
    create_menu();
    create_toolbar();

}

MiniDraw::~MiniDraw()
{}


void MiniDraw::Init()
{
    view_widget_ = new ViewWidget();  // 实例化ViewWidget空间窗口
    setCentralWidget(view_widget_);  // 将ViewWidgwt空间设置为窗口的中心位置
}

void MiniDraw::create_action()
{
    About_Box = new QAction(tr("About"), this);
    connect(About_Box, &QAction::triggered, this, &MiniDraw::AboutBox);

    Line_action = new QAction(QIcon("../icon/line.jpg"), QString("Line"), this);
    connect(Line_action, &QAction::triggered, view_widget_, &ViewWidget::draw_line);

    Free_Line_action = new QAction(QIcon("../icon/freeline.jpg"), QString("Free_Line"), this);
    connect(Free_Line_action, &QAction::triggered, view_widget_, &ViewWidget::draw_free_line);

    Rectangle_action = new QAction(QIcon("../icon/rect.jpg"), QString("Rectangle"), this);
    connect(Rectangle_action, &QAction::triggered, view_widget_, &ViewWidget::draw_rectangle);

    Polygon_action = new QAction(QIcon("../icon/poly.jpg"), QString("Poltgon"), this);
    connect(Polygon_action, &QAction::triggered, view_widget_, &ViewWidget::draw_polygon);

    Circle_action = new QAction(QIcon("../icon/cir.jpg"), QString("Circle"), this);
    connect(Circle_action, &QAction::triggered, view_widget_, &ViewWidget::draw_circle);

    Elliptical_action = new QAction(QIcon("../icon/ellip.jpg"), QString("Elliptical"), this);
    connect(Elliptical_action, &QAction::triggered, view_widget_, &ViewWidget::draw_elliptical);

    Bezier_Curve_action = new QAction(QIcon("../icon/bezier.jpg"), QString("Bezier_Curve"), this);
    connect(Bezier_Curve_action, &QAction::triggered, view_widget_, &ViewWidget::draw_bezier_curve);

    Eraser_action = new QAction(QIcon("../icon/eraser.jpg"), QString("Eraser"), this);
    connect(Eraser_action, &QAction::triggered, view_widget_, &ViewWidget::eraser);

    StepBack_action = new QAction(QIcon("../icon/stepback.jpg"), QString("StepBack"), this);
    connect(StepBack_action, &QAction::triggered, view_widget_, &ViewWidget::stepBack);
}


void MiniDraw::create_toolbar()
{
    ToolBar = addToolBar(tr("&toolbar"));

    ToolBar->addAction(Line_action);
    ToolBar->addAction(Free_Line_action);
    ToolBar->addAction(Rectangle_action);
    ToolBar->addAction(Polygon_action);
    ToolBar->addAction(Circle_action);
    ToolBar->addAction(Elliptical_action);
    ToolBar->addAction(Bezier_Curve_action);
    ToolBar->addAction(Eraser_action);
    ToolBar->addAction(StepBack_action);

    ToolBar->setIconSize(QSize(24, 24));
    ToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    
}

void MiniDraw::create_menu()
{
    Menu = menuBar()->addMenu(tr("&Menu"));
    Menu->addAction(About_Box);
}



void MiniDraw::AboutBox()
{
    QMessageBox::about(this, tr("ABOUT"),
        tr("USTC_CG Assignment_01\n"
            "CliverChen 2022/12/13 in Beijing"));
}