#include "scriptwindow.h"
#include "ui_scriptwindow.h"
#include<QDebug>
#include "QMessageBox"


scriptwindow::scriptwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scriptwindow)
{
    ui->setupUi(this);
}

scriptwindow::~scriptwindow()
{
    delete ui;
}

void scriptwindow::on_doneButton_clicked()
{
    QString allText = ui->plainTextEdit->toPlainText();
    QString fWords = allText.mid(0,6); //get first 6 letter from string
    if(fWords == "Insert" || fWords == "Select" || fWords == "Delete" || fWords == "Update"){ //verifica si es correcta la sintaxis
        qDebug()<<fWords+" ak7";
        close();
    }else{
        QMessageBox::critical(this,tr("ERROR"),tr("Ingresar un sintaxis correcta"));
        ui->plainTextEdit->clear();
        qDebug()<<"MAMO";
    }

    //(INSERT, SELECT, DELETE y UPDATE).
}
