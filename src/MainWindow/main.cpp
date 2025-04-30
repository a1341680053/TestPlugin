#include <iostream>
#include <QApplication>
#include "PluginWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PluginWidget w;
    w.show();
    return a.exec();
}