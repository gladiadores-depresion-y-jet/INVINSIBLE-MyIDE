#ifndef NEWPHOTO_H
#define NEWPHOTO_H

#include <QDialog>

namespace Ui {
class newphoto;
}

class newphoto : public QDialog
{
    Q_OBJECT

public:
    explicit newphoto(QWidget *parent = nullptr);
    ~newphoto();
    QString getNombre();
    QString getAutor();
    QString getAno();
    QString getTamano();
    QString getDescrip();
    QString getGalery();

private slots:
    void on_ImagenBoton_clicked();

    void on_doneBoton_clicked();

private:
    Ui::newphoto *ui;
};

#endif // NEWPHOTO_H
