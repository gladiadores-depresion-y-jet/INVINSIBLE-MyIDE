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
        this->loadAll("", item);

        updated = true;
        return;
    }

    ui->tableWidget->setRowCount(0); //filas de la tabla igual a 0
    if(column == 0){
        qDebug() << item->text(0);

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

                ui->tableWidget->setRowCount(1);
                ui->tableWidget->setItem(0,0, new QTableWidgetItem(item->text(0)));
                ui->tableWidget->setItem(0,1, new QTableWidgetItem(item->text(1)));
                ui->tableWidget->setItem(0,2, new QTableWidgetItem(item->text(2)));
                ui->tableWidget->setItem(0,3, new QTableWidgetItem(item->text(3)));
                ui->tableWidget->setItem(0,4, new QTableWidgetItem(item->text(4)));

                qDebug()<<item->whatsThis(0);
                qDebug()<<item->parent()->text(0);


            }else{
                int hijos = item->childCount();
                ui->tableWidget->setRowCount(hijos);

                for(int i = 0; i < hijos; i++){
                    //inserta 1 fila

                    ui->tableWidget->setItem(i,0, new QTableWidgetItem(item->child(i)->text(0)));
                    ui->tableWidget->setItem(i,1, new QTableWidgetItem(item->child(i)->text(1)));
                    ui->tableWidget->setItem(i,2, new QTableWidgetItem(item->child(i)->text(2)));
                    ui->tableWidget->setItem(i,3, new QTableWidgetItem(item->child(i)->text(3)));
                    ui->tableWidget->setItem(i,4, new QTableWidgetItem(item->child(i)->text(4)));

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


/**
 * @brief reload the entire table with new metadata
 * @param Json
 * @param item
 */
void MainWindow::loadAll(string Json, QTreeWidgetItem *item){
    ui->tableWidget->clear(); //borra la tabla
    std::string ipAdress = "192.168.100.9", port = "9080";
    Requests *requests = new Requests(ipAdress, port);

    std::string resp1 = "";
    std::string answer;
    answer = requests->sendPostRequest(resp1, RESTORE);

    QString qstr = QString::fromStdString(answer); //string to Qstring
    qDebug()<<qstr;

    ptree json = jm.stringToPtree(answer); //string to Json
    int num = json.get<int>("NUM");
    for(int i = 0; i < num; i++){
        ptree jsonGalery = jm.stringToPtree(json.get<string>("Galery"+to_string(i)));
        std::string nodeName = jsonGalery.get<string>("Name"); //Galery's name
        QString Pgalery = QString::fromStdString(nodeName);

        newGalery(item, Pgalery);

        int numImages = jsonGalery.get<int>("NumImages");
        for(int j = 0 ; j<numImages ; j++){
            ptree jsonImage = jm.stringToPtree(jsonGalery.get<string>("Image"+to_string(j)));
            std::string name = jsonImage.get<string>("name");
            std::string author = jsonImage.get<string>("author");
            std::string year = jsonImage.get<string>("year");
            std::string size = jsonImage.get<string>("size");
            std::string description = jsonImage.get<string>("description");
            int code = stoi(jsonImage.get<string>("code"));

            QString Pname = QString::fromStdString(name);
            QString Pauthor = QString::fromStdString(author);
            QString Pyear = QString::fromStdString(year);
            QString Psize = QString::fromStdString(size);
            QString Pdescription = QString::fromStdString(description);

            newPhoto(item, Pname, Pauthor, Pyear, Psize, Pdescription, Pgalery, code); //add a new child of DATABASE
        }
    }
}

/**
 * @brief loads only a single galery
 * @param Json
 * @param item
 */
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


/**
 * @brief loads a single photo
 * @param Json
 * @param item
 */
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

