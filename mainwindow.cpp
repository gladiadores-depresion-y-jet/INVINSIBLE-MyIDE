#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include "scriptwindow.h"


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
    ui->treeWidget->findItems("Galeria 1",Qt::MatchExactly);

    if(column == 0){

        if(item->text(0)=="Foto 1"){
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Foto1"));
            ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Camacho el sabroso"));
            ui->tableWidget->setItem(0, 2, new QTableWidgetItem("6969"));
            ui->tableWidget->setItem(0, 3, new QTableWidgetItem("20cm de sabor"));
            ui->tableWidget->setItem(0, 4, new QTableWidgetItem("Chupo y mamo, DABID me llamo"));
        }
        //print the name of the item in column 0
        //We only have 1 column
        if(item->text(0)=="DataBase"){

            gi.setModal(true); //abre ventana de eleccion
            gi.exec();
            if(gi.eleccion()){
                qDebug("1");
                QString nombreFoto = gi.getNombreP();
                QString nombreGaleria = gi.getGaleryP();
                newPhoto(item, nombreFoto, nombreGaleria); //add a new child of DATABASE
            }else{
                QString nombreGalery = gi.getNameG();
                newGalery(item,nombreGalery);
            }

        }
    }
}

void MainWindow::newPhoto(QTreeWidgetItem *item, QString nombre, QString galery){
    for(int i=0; i < item->childCount(); i++){
        if(item->child(i)->text(0) == galery){
            QTreeWidgetItem *itm = new QTreeWidgetItem(item->child(i));
            itm->setText(0, nombre);
            ui->treeWidget->addTopLevelItem(itm);
            break;
        }
    }
    fillTable(gi.getNombreP(),gi.getAutorP(),gi.getAnoP(),gi.getTamanoP(),gi.getDescripP());
    qDebug("MAMAMOS");

}

void MainWindow:: fillTable(QString name, QString autor, QString date, QString lenght, QString description){
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(autor));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(date));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(lenght));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(description));
}

void MainWindow::newGalery(QTreeWidgetItem *item, QString nombre){
    QTreeWidgetItem *itm = new QTreeWidgetItem(item); //por cada galeria creada asignarle un index para meterlo aqui
    itm->setText(0, nombre);
    ui->treeWidget->addTopLevelItem(itm);

}


void MainWindow::on_scriptButton_clicked()
{
    scriptwindow sw;
    sw.setModal(true);
    sw.exec();
}
