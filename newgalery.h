#ifndef NEWGALERY_H
#define NEWGALERY_H

#include <QDialog>
#include <qfiledialog.h>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class newGalery;
}

class newGalery : public QDialog
{
    Q_OBJECT

public:
    explicit newGalery(QWidget *parent = nullptr);
    ~newGalery();
    QString galeryName;
    QString getName();
    void directory();

    QList<QString> list;
    QList<QString> getList();



private slots:
    void on_doneBoton_clicked();

private:
    Ui::newGalery *ui;
};

#endif // NEWGALERY_H
