#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

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
    ui->tableWidget->setRowCount(0); //filas de la tabla igual a 0
    if(column == 0){
        qDebug() << item->text(0);
        //hacer request al server para desplejar informacion

        //print the name of the item in column 0
        //We only have 1 column
        if(item->text(0)=="DataBase"){
            gi.setModal(true); //abre ventana de eleccion
            gi.exec();

            if(gi.eleccion()){
                newPhoto(item, gi.getNombreP(), gi.getGaleryP()); //add a new child of DATABASE
            }else{
                newGalery(item, gi.getNameG());
            }
        }else{
            if(item->child(0) == nullptr){ //=> Galeria esta vacia o es una foto
                qDebug()<<"ZS-miedo";
                ui->tableWidget->setRowCount(1);
                ui->tableWidget->setItem(0,0, new QTableWidgetItem(item->text(0)));
            }else{
                int hijos = item->childCount();
                ui->tableWidget->setRowCount(hijos);
                qDebug()<<hijos;

                /*
                QList<QString> list = gi.getList();
                list.removeFirst();
                list.removeFirst();
                qDebug()<<list.length();

                while(hijos != list.length()){
                    list.append(nameToAdd);
                }
                */

                for(int i = 0; i < hijos; i++){
                    //inserta 1 fila
                    //QString wila = item->child(i)->text(0); delete
                    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(item->child(i)->text(0))); //agarra los hijos del arbol y los pone en la tabla
                    //este paso se tiene que hacer desde la metadata que envia el server
                    //puede que en newgalery haya una lista que ya no se ese utilizando
                }
                //meter los valores de la metada de las canciones
            }
        }
    }
}

void MainWindow::newPhoto(QTreeWidgetItem *item, QString nombre, QString galery){ //add new photo to a galery
    for(int i=0; i < item->childCount(); i++){
        if(item->child(i)->text(0) == galery){
            QTreeWidgetItem *itm = new QTreeWidgetItem(item->child(i));
            itm->setText(0, nombre);
            ui->treeWidget->addTopLevelItem(itm);
            break;
        }
    }
}

void MainWindow::newGalery(QTreeWidgetItem *item, QString nombre){
    QTreeWidgetItem *itm = new QTreeWidgetItem(item);
    itm->setText(0, nombre);
    ui->treeWidget->addTopLevelItem(itm);
    QList<QString> list = gi.getList();
    list.removeFirst();
    list.removeFirst(); //delete two trash elements from list
    int lenght = list.length();
    for(int i = 0; i < lenght; i++){
        newPhoto(item,list.first(),nombre);
        list.removeFirst();
        //qDebug() << list ;
    }
}

void MainWindow::load(string Json){
    ptree json = jm.stringToPtree(Json);
    int num = json.get<int>("NUM");
    for(int i = 0; i < num; i++){
        ptree jsonGalery = jm.stringToPtree(json.get<string>("Galery"+i));
        string nodeName = jsonGalery.get<string>("Name"); //Galery's name
      //  newGalery(item, nodeName);

        int numImages = jsonGalery.get<int>("NumImages");
        for(int j = 0 ; j<numImages ; j++){
            ptree jsonImage = jm.stringToPtree(jsonGalery.get<string>("Image"+j));
            string name = jsonImage.get<string>("name");

        //    newPhoto(item, name, nodeName); //add a new child of DATABASE

        }
    }

}


void MainWindow::on_scriptButton_clicked()
{
    scriptwindow sw;
    sw.setModal(true);
    sw.exec();
}
