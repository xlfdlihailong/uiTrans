﻿#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qlib::loadQss(&a,"psblack.css");
    qlib::initLog();

    MainWindow w;
    w.show();

    return a.exec();
}
