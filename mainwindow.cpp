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

    if(!updated){
       this->load("", item);
        updated = true;
    }

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
                newPhoto(item, gi.getNombreP(), gi.getGaleryP(),0); //add a new child of DATABASE
            }else{
                newGalery(item, gi.getNameG());
            }
        }else{
            if(item->child(0) == nullptr){ //=> Galeria esta vacia o es una foto
                ui->tableWidget->setRowCount(1);
                ui->tableWidget->setItem(0,0, new QTableWidgetItem(item->text(0)));
                qDebug()<<item->whatsThis(0);
                qDebug()<< item->parent()->text(0);
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
                }
                //meter los valores de la metada de las canciones
            }
        }
    }
}

void MainWindow::newPhoto(QTreeWidgetItem *item, QString nombre, QString galery, int code){ //add new photo to a galery

    for(int i=0; i < item->childCount(); i++){
        if(item->child(i)->text(0) == galery){
            QTreeWidgetItem *itm = new QTreeWidgetItem(item->child(i));
            itm->setText(0, nombre);
            itm->setWhatsThis(0,QString::fromStdString(to_string(code)));
            qDebug()<<itm->whatsThis(0);
            ui->treeWidget->addTopLevelItem(itm);
            break;
        }
    }
}

void MainWindow::newGalery(QTreeWidgetItem *item, QString nombre){
    QTreeWidgetItem *itm = new QTreeWidgetItem(item);
    itm->setText(0, nombre);
    ui->treeWidget->addTopLevelItem(itm);



  /*  QList<QString> list = gi.getList();
    list.removeFirst();
    list.removeFirst(); //delete two trash elements from list
    int lenght = list.length();
    for(int i = 0; i < lenght; i++){
        newPhoto(item,list.first(),nombre);
        list.removeFirst();
        //qDebug() << list ;
    }*/
}



void MainWindow::load(string Json, QTreeWidgetItem *item){
    ima1.put("name","sing");
    ima1.put("author","GARZA");
    ima1.put("year","2019");
    ima1.put("size","2000");
    ima1.put("description","this is a description");
    ima1.put("code","1");

    ima2.put("name","daniel");
    ima2.put("author","DAVID");
    ima2.put("year","2017");
    ima2.put("size","3000");
    ima2.put("description","fucking shit");\
    ima2.put("code","2");

    Galery.put("NumImages",2);
    Galery.put("Name", "Fotos");
    Galery.put("Image0",jsonM.ptreeToString(ima1));
    Galery.put("Image1",jsonM.ptreeToString(ima2));

    prueba.put("NUM",1);
    prueba.put("Galery0",jsonM.ptreeToString(Galery));

    string valor = jsonM.ptreeToString(prueba);
    QString qstr = QString::fromStdString(valor); //string to Qstring
    qDebug()<<qstr;




    ptree json = jm.stringToPtree(valor);
    int num = json.get<int>("NUM");
    for(int i = 0; i < num; i++){
        ptree jsonGalery = jm.stringToPtree(json.get<string>("Galery"+to_string(i)));
        string nodeName = jsonGalery.get<string>("Name"); //Galery's name
        QString qstr1 = QString::fromStdString(nodeName);

        newGalery(item, qstr1);

        int numImages = jsonGalery.get<int>("NumImages");
        for(int j = 0 ; j<numImages ; j++){
            ptree jsonImage = jm.stringToPtree(jsonGalery.get<string>("Image"+to_string(j)));
            string name = jsonImage.get<string>("name");
            int code = stoi(jsonImage.get<string>("code"));
            QString qstr2 = QString::fromStdString(name);

            newPhoto(item, qstr2, qstr1, code); //add a new child of DATABASE

        }
    }

}


void MainWindow::on_scriptButton_clicked()
{
    scriptwindow sw;
    sw.setModal(true);
    sw.exec();
}
