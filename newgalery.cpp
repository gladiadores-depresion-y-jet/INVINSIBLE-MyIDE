#include "newgalery.h"
#include "ui_newgalery.h"

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

void newGalery::on_doneBoton_clicked()
{
    if(ui->nameText->text() == ""){
        QMessageBox::critical(this,tr("ERROR"),tr("No hay Galeria creada")); //ventana emergente
    }else{
        close();
    }
}

void newGalery::directory(){
    list.clear(); //lista nueva
    QString dir = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
    QFileInfo fi(dir);
    galeryName = fi.fileName();
    qDebug() << galeryName; //name of the folder/galery
    QDir myDir(dir);
    foreach (QFileInfo myInfo, myDir.entryInfoList()) {
        //access to the name of every image file
        list.append(myInfo.fileName());
    }
}

QList<QString> newGalery::getList(){
    return list;
}

QString newGalery::getName(){
    list.append(ui->nameText->text());
    return ui->nameText->text();
}


