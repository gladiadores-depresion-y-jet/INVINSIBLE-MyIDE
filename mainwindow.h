#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <galeryorimage.h>
#include <newphoto.h>
#include <QDebug>
#include <scriptwindow.h>
#include <jsonmanager.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <client/Requests.h>
#include <synthaxParser/Parser.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using boost::property_tree::ptree;
using nlohmann::json;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * crear una nueva foto para ser mostrada en la interfaz y enviada al servidor
     * @param item del arbol de la interfaz
     * @param name: nombre de la foto
     * @param author: autor de la foto
     * @param year: ano de la foto
     * @param size: tamano de la foto
     * @param description: descripcion de la foto
     * @param galery: galeria donde se encuentra la foto
     * @param code: id de la foto
     */
    void newPhoto(QTreeWidgetItem *item, QString name, QString author, QString year, QString size, QString description, QString galery, int code);

    /**
     * crea una nueva galeria para ser mostrada en la interfaz y enviada al servidor
     * @param item del arbol de la interfaz
     * @param nombre de la galeria
     */
    void newGalery(QTreeWidgetItem *item, QString nombre);

    /**
     * recarga la tabla entera con la nueva metadata
     * @param QTreeWifgetItem, indica a cual item del arbol de la interfaz se le tiene que agregar a la metadata
     */
    void loadAll(QTreeWidgetItem *item);

    /**
     * @brief loads only a single galery
     * @param Json
     * @param item
     */
    void loadGalery(string Json, QTreeWidgetItem *item);


    /**
     * @brief loads a single photo
     * @param Json
     * @param item
     */
    void loadPhoto(string Json);


    jsonmanager jm;
    GaleryorImage gi;
    newphoto np;

private slots:
    /**
     * funcion de doble click para desplegar nueva informacion en el arbol
     * @param item del arbol de la interfaz
     * @param column donde se encuentra el item seleccionado
     */
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    /**
     * boton para abrir la interfaz de los scripts
     */
    void on_scriptButton_clicked();

private:
    Ui::MainWindow *ui;
};

static bool updated = false;


#endif // MAINWINDOW_H
