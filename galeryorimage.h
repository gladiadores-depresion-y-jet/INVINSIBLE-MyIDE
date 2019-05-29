#ifndef GALERYORIMAGE_H
#define GALERYORIMAGE_H

#include <QDialog>
#include "newphoto.h"
#include "newgalery.h"
namespace Ui {
class GaleryorImage;
}

class GaleryorImage : public QDialog
{
    Q_OBJECT

public:
    explicit GaleryorImage(QWidget *parent = nullptr);
    ~GaleryorImage();
    QString getNombreP();
    QString getAutorP();
    QString getAnoP();
    QString getTamanoP();
    QString getDescripP();
    QString getNameG();
    QString getGaleryP();
    newGalery nG;
    newphoto nf;
    bool choice;

    bool eleccion();

private slots:
    void on_FotoBoton_clicked();

    void on_GaleriaBoton_clicked();

private:
    Ui::GaleryorImage *ui;
};

#endif // GALERYORIMAGE_H
