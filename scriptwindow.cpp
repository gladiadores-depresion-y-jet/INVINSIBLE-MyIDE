#include "scriptwindow.h"
#include "ui_scriptwindow.h"

scriptwindow::scriptwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scriptwindow)
{
    ui->setupUi(this);
}

scriptwindow::~scriptwindow()
{
    delete ui;
}
