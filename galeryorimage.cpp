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

/**
  metodo para agregar nueva image
 * @brief GaleryorImage::on_FotoBoton_clicked
 */
void GaleryorImage::on_FotoBoton_clicked()
{
    if(!nG.getList().isEmpty()){ //lista para ver si hay una galeria
        nf.setModal(true);
        nf.exec();
        choice = true; //boolenado para ver que opcion se tomo
        close();
    }else{
        QMessageBox::critical(this,tr("ERROR"),tr("No hay Galeria creada")); //ventana emergente

    }

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
   // nG.directory();
    choice = false;
    close();

}

bool GaleryorImage::eleccion(){
    return choice;
}

QString GaleryorImage::getNameG(){
    return nG.getName();
}
QList<QString> GaleryorImage::getList(){
    return nG.getList();
}
