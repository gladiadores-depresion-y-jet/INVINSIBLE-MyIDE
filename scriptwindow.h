#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

#include <QDialog>

namespace Ui {
class scriptwindow;
}

class scriptwindow : public QDialog
{
    Q_OBJECT

public:
    explicit scriptwindow(QWidget *parent = nullptr);
    ~scriptwindow();

private:
    Ui::scriptwindow *ui;
};

#endif // SCRIPTWINDOW_H
