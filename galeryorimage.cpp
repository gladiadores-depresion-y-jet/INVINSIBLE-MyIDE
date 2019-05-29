#include "galeryorimage.h"
#include "ui_galeryorimage.h"
GaleryorImage::GaleryorImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaleryorImage)
{
    ui->setupUi(this);

}

GaleryorImage::~GaleryorImage()
{
    delete ui;
}

void GaleryorImage::on_FotoBoton_clicked()
{

    nf.setModal(true);
    nf.exec();
    choice = true;
    close();

}

QString GaleryorImage:: getNombreP(){
    return nf.getNombre();
}
QString GaleryorImage:: getAutorP(){
    return nf.getAutor();
}
QString GaleryorImage:: getAnoP(){
    return nf.getAno();
}
QString GaleryorImage:: getTamanoP(){
    return nf.getTamano();
}
QString GaleryorImage:: getDescripP(){
    return nf.getDescrip();
}
QString GaleryorImage:: getGaleryP(){
    return nf.getGalery();
}

void GaleryorImage::on_GaleriaBoton_clicked()
{
    nG.setModal(true);
    nG.exec();
    choice = false;
    close();

}

bool GaleryorImage::eleccion(){
    return choice;

}

QString GaleryorImage::getNameG(){
    return nG.getName();
}
