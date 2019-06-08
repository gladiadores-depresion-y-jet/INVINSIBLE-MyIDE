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
    void newPhoto(QTreeWidgetItem *item, QString nombre, QString galery);
    void newGalery(QTreeWidgetItem *item, QString nombre);
    void load(string Json);

    jsonmanager jm;
    GaleryorImage gi;
    newphoto np;
    ptree p;

private slots:
    void on_treeWidget_expanded(const QModelIndex &index);
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_tableWidget_cellActivated(int row, int column);
    void on_scriptButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
