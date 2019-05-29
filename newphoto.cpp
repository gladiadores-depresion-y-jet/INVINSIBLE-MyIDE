#include "newphoto.h"
#include "ui_newphoto.h"
#include "QFileDialog"
#include "QPixmap"

newphoto::newphoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newphoto)
{
    ui->setupUi(this);
}

newphoto::~newphoto()
{
    delete ui;
}

void newphoto::on_ImagenBoton_clicked()
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

void newphoto::on_doneBoton_clicked()
{
    if(ui->nombreText->text() != "" && ui->autorText->text() != "" && ui->anoText->text() != "" && ui->tamanoText->text() != "" && ui->descripcionText->text() != "" && ui->galeriaText->text() != ""){

        //mandar metadata

        qDebug("ak1000");
        close();
    }else{
        qDebug("falta dato"); //crear ventana emergente
    }
}


QString newphoto:: getNombre(){
    return ui->nombreText->text();
}
QString newphoto:: getAutor(){
    return ui->autorText->text();
}
QString newphoto:: getAno(){
    return ui->anoText->text();
}
QString newphoto:: getTamano(){
    return ui->tamanoText->text();
}
QString newphoto:: getDescrip(){
    return ui->descripcionText->text();
}
QString newphoto:: getGalery(){
    return ui->galeriaText->text();
}
