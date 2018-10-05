#include <QApplication>
#include <iostream>
#include <QDebug>
#include "include/core/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main;
    main.show();
    return a.exec();
}
