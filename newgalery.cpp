#include "newgalery.h"
#include "ui_newgalery.h"

#include <qfiledialog.h>
#include "QDebug"

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
    close();
}

void newGalery::directory(){
    list.clear();
    QString dir = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());

    QFileInfo fi(dir);
    galeryName = fi.fileName();
    qDebug() << galeryName; //name of the folder/galery
    QDir myDir(dir);
    foreach (QFileInfo myInfo, myDir.entryInfoList()) {
        //access to the name of a image file
        list.append(myInfo.fileName());
        //qDebug() << list;

    }
}
QList<QString> newGalery::getList(){
    return list;
}

QString newGalery::getName(){
    //QString nameGalery = ui->nameText->text();
    return galeryName;
}


