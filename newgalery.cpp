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
    close();
}

QString newGalery::getName(){
    QString nameGalery = ui->nameText->text();
    return nameGalery;
}


