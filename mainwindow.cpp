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
<<<<<<< HEAD
        this->loadAll("", item);
=======
        this->load("", item);
>>>>>>> b6e074daba2fc150e4d6def273e1dbc772a495ce
        updated = true;
        return;
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
                newPhoto(item, gi.getNombreP(), gi.getGaleryP(),"","","","",0); //add a new child of DATABASE
            }else{
                newGalery(item, gi.getNameG());
            }
        }else{
            if(item->child(0) == nullptr){ //=> Galeria esta vacia o es una foto
                if(item->text(0)==""){
                    string select = "SELECT (name, author, year, size, description) FROM " + string(item->text(0).toUtf8().constData());

                    //mandar select
                    //recibir json
                    //json to string
                    //loadPhoto(stringJson, item);

                }else{
                    ui->tableWidget->setRowCount(1);
                    ui->tableWidget->setItem(0,0, new QTableWidgetItem(item->text(0)));
                    ui->tableWidget->setItem(0,1, new QTableWidgetItem(item->text(1)));
                    ui->tableWidget->setItem(0,2, new QTableWidgetItem(item->text(2)));
                    ui->tableWidget->setItem(0,3, new QTableWidgetItem(item->text(3)));
                    ui->tableWidget->setItem(0,4, new QTableWidgetItem(item->text(4)));

                    qDebug()<<item->whatsThis(0);
                    qDebug()<<item->parent()->text(0);
                }

            }else{
                int hijos = item->childCount();
                ui->tableWidget->setRowCount(hijos);
<<<<<<< HEAD

                for(int i = 0; i < hijos; i++){
                    //inserta 1 fila
                    if(item->child(0)->text(0)==""){
                        string select = "SELECT (name, author, year, size, description) FROM " + string(item->text(0).toUtf8().constData());
                        //mandar select
                        //recibir json
                        //json to string
                        //loadGalery(stringJson, item);
                    }else{
                        ui->tableWidget->setItem(i,0, new QTableWidgetItem(item->child(i)->text(0)));
                        ui->tableWidget->setItem(i,1, new QTableWidgetItem(item->child(i)->text(1)));
                        ui->tableWidget->setItem(i,2, new QTableWidgetItem(item->child(i)->text(2)));
                        ui->tableWidget->setItem(i,3, new QTableWidgetItem(item->child(i)->text(3)));
                        ui->tableWidget->setItem(i,4, new QTableWidgetItem(item->child(i)->text(4)));
                    }
=======
                qDebug()<<hijos;

                for(int i = 0; i < hijos; i++){
                    //inserta 1 fila
                    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(item->child(i)->text(0))); //agarra los hijos del arbol y los pone en la tabla

                    //este paso se tiene que hacer desde la metadata que envia el server
>>>>>>> b6e074daba2fc150e4d6def273e1dbc772a495ce
                }
            }
        }
    }
}

void MainWindow::newPhoto(QTreeWidgetItem *item, QString name, QString author, QString year, QString size, QString description, QString galery, int code){ //add new photo to a galery

    for(int i=0; i < item->childCount(); i++){
        if(item->child(i)->text(0) == galery){
            QTreeWidgetItem *itm = new QTreeWidgetItem(item->child(i));
            itm->setText(0, name);
            itm->setText(1, author);
            itm->setText(2, year);
            itm->setText(3, size);
            itm->setText(4, description);
            qDebug()<<itm->text(4);
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem(item->text(4)));

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
}


<<<<<<< HEAD

void MainWindow::loadAll(string Json, QTreeWidgetItem *item){
=======
void MainWindow::load(string Json, QTreeWidgetItem *item){
>>>>>>> b6e074daba2fc150e4d6def273e1dbc772a495ce
    /*
     * Json de Garza
*/

    //Crea Json
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

    //Json to String
    string valor = jsonM.ptreeToString(prueba);
    QString qstr = QString::fromStdString(valor); //string to Qstring
    qDebug()<<qstr;

    std::string ipAdress = "192.168.100.9", port = "9080";
    Requests *requests = new Requests(ipAdress, port);

    ptree json = jm.stringToPtree(valor);
    int num = json.get<int>("NUM");
    for(int i = 0; i < num; i++){
        ptree jsonGalery = jm.stringToPtree(json.get<string>("Galery"+to_string(i)));
        string nodeName = jsonGalery.get<string>("Name"); //Galery's name
<<<<<<< HEAD
        QString Pgalery = QString::fromStdString(nodeName);

        newGalery(item, Pgalery);
=======
        QString galeryN = QString::fromStdString(nodeName);

        //add new Galery
        newGalery(item, galeryN);
>>>>>>> b6e074daba2fc150e4d6def273e1dbc772a495ce

        int numImages = jsonGalery.get<int>("NumImages");
        for(int j = 0 ; j<numImages ; j++){
            ptree jsonImage = jm.stringToPtree(jsonGalery.get<string>("Image"+to_string(j)));
            string name = jsonImage.get<string>("name");
            string author = jsonImage.get<string>("author");
            string year = jsonImage.get<string>("year");
            string size = jsonImage.get<string>("size");
            string description = jsonImage.get<string>("description");
            int code = stoi(jsonImage.get<string>("code"));
<<<<<<< HEAD

            QString Pname = QString::fromStdString(name);
            QString Pauthor = QString::fromStdString(author);
            QString Pyear = QString::fromStdString(year);
            QString Psize = QString::fromStdString(size);
            QString Pdescription = QString::fromStdString(description);
            newPhoto(item, Pname, Pauthor, Pyear, Psize, Pdescription, Pgalery, code); //add a new child of DATABASE
=======
            QString photoN = QString::fromStdString(name);

            //add new photo
            newPhoto(item, photoN, galeryN, code); //add a new child of DATABASE
>>>>>>> b6e074daba2fc150e4d6def273e1dbc772a495ce

        }
    }

}

void MainWindow::loadGalery(string Json, QTreeWidgetItem *item){

    ptree json = jm.stringToPtree(Json);
    int numImages = json.get<int>("NumImages");
    for(int j = 0 ; j<numImages ; j++){
        ptree jsonImage = jm.stringToPtree(json.get<string>("Image"+to_string(j)));
        string name = jsonImage.get<string>("name");
        string author = jsonImage.get<string>("author");
        string year = jsonImage.get<string>("year");
        string size = jsonImage.get<string>("size");
        string description = jsonImage.get<string>("description");
        int code = stoi(jsonImage.get<string>("code"));

        QString Pname = QString::fromStdString(name);
        QString Pauthor = QString::fromStdString(author);
        QString Pyear = QString::fromStdString(year);
        QString Psize = QString::fromStdString(size);
        QString Pdescription = QString::fromStdString(description);
        newPhoto(item, Pname, Pauthor, Pyear, Psize, Pdescription, item->parent()->text(0), code); //add a new child of DATABASE
    }
}



void MainWindow::loadPhoto(string Json, QTreeWidgetItem *item){
    ptree json = jm.stringToPtree(Json);

    //ptree jsonImage = jm.stringToPtree(jsonGalery.get<string>("Image"+to_string(0)));
    string name = json.get<string>("name");
    string author = json.get<string>("author");
    string year = json.get<string>("year");
    string size = json.get<string>("size");
    string description = json.get<string>("description");
    int code = stoi(json.get<string>("code"));

    QString Pname = QString::fromStdString(name);
    QString Pauthor = QString::fromStdString(author);
    QString Pyear = QString::fromStdString(year);
    QString Psize = QString::fromStdString(size);
    QString Pdescription = QString::fromStdString(description);
    newPhoto(item, Pname, Pauthor, Pyear, Psize, Pdescription, item->parent()->text(0), code); //add a new child of DATABASE

}


void MainWindow::on_scriptButton_clicked()
{
    scriptwindow sw;
    sw.setModal(true);
    sw.exec();
}
