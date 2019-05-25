#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_treeWidget_expanded(const QModelIndex &index);
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);


    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
