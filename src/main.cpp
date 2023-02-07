#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(w.screen()->availableGeometry().center().x() - (w.frameGeometry().right()/2),
           w.screen()->availableGeometry().center().y() - (w.frameGeometry().bottom()/2));
    w.show();
    return a.exec();
}
