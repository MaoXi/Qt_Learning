﻿#include "widget.h"
#include <QApplication>
#include"QStyleFactory"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));
    Widget w;
    w.show();

    return a.exec();
}
