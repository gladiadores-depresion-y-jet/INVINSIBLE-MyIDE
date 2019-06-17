#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <galeryorimage.h>
#include <newphoto.h>
#include <QDebug>
#include <scriptwindow.h>
#include <jsonmanager.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <client/Requests.h>
#include <synthaxParser/Parser.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using boost::property_tree::ptree;
using nlohmann::json;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newPhoto(QTreeWidgetItem *item, QString name, QString author, QString year, QString size, QString description, QString galery, int code);
    void newGalery(QTreeWidgetItem *item, QString nombre);
    void loadAll(QTreeWidgetItem *item);
    void loadGalery(string Json, QTreeWidgetItem *item);
    void loadPhoto(string Json, QTreeWidgetItem *item);


    jsonmanager jm;
    GaleryorImage gi;
    newphoto np;


    ptree prueba;
    ptree Galery;
    ptree ima1;
    ptree ima2;
    jsonmanager jsonM = jsonmanager();


private slots:
    void on_treeWidget_expanded(const QModelIndex &index);
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_tableWidget_cellActivated(int row, int column);
    void on_scriptButton_clicked();

    void on_treeWidget_pressed(const QModelIndex &index);

    void on_treeWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

static bool updated = false;


#endif // MAINWINDOW_H
