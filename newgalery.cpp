#include "newgalery.h"
#include "ui_newgalery.h"
#include <mainwindow.h>

newGalery::newGalery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGalery)
{
    ui->setupUi(this);
}

newGalery::~newGalery()
{
    delete ui;
}

/**
 * crea nueva galeria por medio de la interfaz
 */
void newGalery::on_doneBoton_clicked()
{
    if(ui->nameText->text() == ""){
        QMessageBox::critical(this,tr("ERROR"),tr("No hay Galeria creada")); //ventana emergente
    }else{
        std::string galeryName = ui->nameText->text().toUtf8().constData(); //QString to string

        std::string ipAdress = "192.168.100.9", port = "9080";
        Requests *requests = new Requests(ipAdress, port);

        Parser *parser = new Parser();
        json answer;
        answer["table"] = galeryName;
        if (!answer.empty()) {
            std::string enviar = answer.dump();
            std::cout << enviar << std::endl;
            requests->sendPostRequest(enviar, CREATE);
        }
        updated = false;
        close();
    }
}

QList<QString> newGalery::getList(){
    return list;
}

/**
 * devuelve el nombre de la galeria creada
 * @return
 */
QString newGalery::getName(){
    list.append(ui->nameText->text());
    return ui->nameText->text();
}


