#include "mainwindow.h"
#include <QApplication>

#include <jsonmanager.h>
#include <QDebug>
#include <QString>

using nlohmann::json;


int main(int argc, char *argv[])
{

    //sudo apt install libgl1-mesa-dev
   //library needed equis de

    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
