#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QStyleFactory>
//#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");
    MainWindow w;
    w.show();
    //w.show();

    return a.exec();
}
