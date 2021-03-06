#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <client/Requests.h>
#include <synthaxParser/Parser.h>
#include <nlohmann/json.hpp>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <jsonmanager.h>



namespace Ui {
class scriptwindow;
}

class scriptwindow : public QDialog
{
    Q_OBJECT

public:
    explicit scriptwindow(QWidget *parent = nullptr);
    ~scriptwindow();
    jsonmanager jm;
    std::string image;

private slots:
    void on_doneButton_clicked();

private:
    Ui::scriptwindow *ui;
};

#endif // SCRIPTWINDOW_H
