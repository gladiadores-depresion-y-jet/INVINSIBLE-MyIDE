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
        qDebug() << item->text(0);
        //hacer request al server para desplejar informacion


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

                QString nombreFoto = gi.getNombreP();
                QString nombreGaleria = gi.getGaleryP();
                newPhoto(item, nombreFoto, nombreGaleria); //add a new child of DATABASE

            }else{
                newGalery(item, gi.getNameG());
            }
        }else{
            if(item->child(0) == nullptr){ //=> Galeria esta vacia o es una foto
                qDebug()<<"ZS-miedo";
            }else{
                int hijos = item->childCount();

                for(int i = 0; i < hijos; i++){
                    qDebug()<<hijos;
                    ui->tableWidget->insertRow(i+1); //inserta 1 fila
                }
                ui->tableWidget->setItem(1, 0, new QTableWidgetItem("terror"));
                //meter los valores de la metada de las canciones
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
            fillTable(gi.getNombreP(),gi.getAutorP(),gi.getAnoP(),gi.getTamanoP(),gi.getDescripP());
            break;
        }
    }
}

void MainWindow:: fillTable(QString name, QString autor, QString date, QString lenght, QString description){
    //hacer modificacion para que el server mande la info
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(autor));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(date));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(lenght));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(description));
}

void MainWindow::newGalery(QTreeWidgetItem *item, QString nombre){
    QTreeWidgetItem *itm = new QTreeWidgetItem(item);
    itm->setText(0, nombre);
    ui->treeWidget->addTopLevelItem(itm);
    QList<QString> list = gi.getList();
    list.removeFirst();
    list.removeFirst();
    int lenght = list.length();
    for(int i = 0; i < lenght; i++){

        newPhoto(item,list.first(),nombre);
        list.removeFirst();
        qDebug() << list ;
    }



}
void MainWindow::on_scriptButton_clicked()
{
    scriptwindow sw;
    sw.setModal(true);
    sw.exec();
}
