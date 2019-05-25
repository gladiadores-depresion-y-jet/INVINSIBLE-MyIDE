#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    if(column == 0){
        qDebug() << item->text(0);
        if(item->text(0)=="Foto 1"){
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Foto1"));
            ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Camacho el sabroso"));
            ui->tableWidget->setItem(0, 2, new QTableWidgetItem("6969"));
            ui->tableWidget->setItem(0, 3, new QTableWidgetItem("20cm de sabor"));
            ui->tableWidget->setItem(0, 4, new QTableWidgetItem("Chupo y mamo, DABID me llamo"));
        }
        //print the name of the item in column 0
        //We only have 1 column

    }

}


