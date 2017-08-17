#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <keybroad_def.h>
#include <wiringPi.h>
#include <crypt.h>
#include <QDebug>
#include <QTimer>
#include <page_def.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Page_Def pagedef;
    void setText();
    void clearText();
    void setTextsp(QString sp);
    void setTextbs();

public slots:
    void HoliLoop();
};

#endif // MAINWINDOW_H
