#include "mainwindow.h"
#include <QApplication>
#include <keybroad_def.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                     | Qt::WindowCloseButtonHint);
    w.showFullScreen();

    return a.exec();
}
