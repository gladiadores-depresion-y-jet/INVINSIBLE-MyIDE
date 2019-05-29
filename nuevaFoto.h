#ifndef NUEVAFOTO_H
#define NUEVAFOTO_H

#include <QDialog>

namespace Ui {
class nuevaFoto;
}

class nuevaFoto : public QDialog
{
    Q_OBJECT

public:
    explicit nuevaFoto(QWidget *parent = nullptr);
    ~nuevaFoto();
    QString getNombre();
    QString getAutor();
    QString getAno();
    QString getTamano();
    QString getDescrip();

private slots:
    void on_doneBoton_clicked();

    void on_ImagenBoton_clicked();

private:
    Ui::nuevaFoto *ui;
};

#endif // NUEVAFOTO_H
