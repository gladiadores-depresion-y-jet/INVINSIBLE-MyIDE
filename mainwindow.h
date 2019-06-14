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

using boost::property_tree::ptree;



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
    void loadAll(string Json, QTreeWidgetItem *item);
    void loadGalery(string Json, QTreeWidgetItem *item);
    void loadPhoto(string Json, QTreeWidgetItem *item);


    jsonmanager jm;
    GaleryorImage gi;
    newphoto np;

    bool updated = false;
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
