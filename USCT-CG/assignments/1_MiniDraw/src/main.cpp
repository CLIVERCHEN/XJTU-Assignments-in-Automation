#include "MiniDraw.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MiniDraw w;
    w.setWindowIcon(QIcon("../icon/exe.jpg"));
    w.show();
    return a.exec();
}
