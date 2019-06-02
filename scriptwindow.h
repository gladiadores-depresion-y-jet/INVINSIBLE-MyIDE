#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class scriptwindow;
}

class scriptwindow : public QDialog
{
    Q_OBJECT

public:
    explicit scriptwindow(QWidget *parent = nullptr);
    ~scriptwindow();

private slots:
    void on_doneButton_clicked();

private:
    Ui::scriptwindow *ui;
};

#endif // SCRIPTWINDOW_H
