#include "nuevaFoto.h"
#include "ui_nuevafoto.h"
#include "QFileDialog"
#include "QPixmap"
#include "mainwindow.h"

nuevaFoto::nuevaFoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nuevaFoto)
{
    ui->setupUi(this);
}

nuevaFoto::~nuevaFoto()
{
    delete ui;
}

void nuevaFoto::on_ImagenBoton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Image (*.jpeg)"
                );
    QPixmap pix(filename);
    ui->fotolabel->setPixmap(pix.scaled(350,350,Qt::KeepAspectRatio));
}

void nuevaFoto::on_doneBoton_clicked()
{
    if(ui->nombreText->text() != "" && ui->autorText->text() != "" && ui->anoText->text() != "" && ui->tamanoText->text() != ""){

        //mandar metadata

        qDebug("ak1000");
        close();
    }else{
        qDebug("falta dato"); //crear ventana emergente
    }
}

QString nuevaFoto:: getNombre(){
    return ui->nombreText->text();
}

QString nuevaFoto:: getAutor(){
    return ui->autorText->text();
}
QString nuevaFoto:: getAno(){
    return ui->anoText->text();
}
QString nuevaFoto:: getTamano(){
    return ui->tamanoText->text();
}
QString nuevaFoto:: getDescrip(){
    return ui->descripcionText->text();
}
