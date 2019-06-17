#include "newphoto.h"
#include "ui_newphoto.h"
#include <mainwindow.h>

newphoto::newphoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newphoto)
{
    ui->setupUi(this);
}

newphoto::~newphoto()
{
    delete ui;
}

/**
 * selecciona una foto en disco y la convierte a bits
 */
void newphoto::on_ImagenBoton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Image (*.jpeg)"
                ); //opens .jpeg files only
    QPixmap pix(filename);
    std::string filenameString = filename.toUtf8().constData(); //filename string
    ui->fotolabel->setPixmap(pix.scaled(350,350,Qt::KeepAspectRatio)); //set the image into the window

    //METADATA METODO DE CAMACHO
    std::ifstream ifs(filenameString, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    char* buffer = new char[pos];
    ifs.seekg(0, std::ios::beg);
    ifs.read(buffer, pos);
    std::vector<char> data(buffer, buffer+int(pos));
    //pasar data a camacho

}

/**
 * envia una foto a la base de datos (data y metadata)
 */
void newphoto::on_doneBoton_clicked()
{
    if(ui->nombreText->text() != "" && ui->autorText->text() != "" && ui->anoText->text() != "" && ui->tamanoText->text() != "" && ui->descripcionText->text() != "" && ui->galeriaText->text() != ""){
        std::string nameP = ui->nombreText->text().toUtf8().constData();
        std::string authorP = ui->autorText->text().toUtf8().constData();
        std::string ageP = ui->anoText->text().toUtf8().constData();
        std::string sizeP = ui->tamanoText->text().toUtf8().constData();
        std::string descriptionP = ui->descripcionText->text().toUtf8().constData();
        std::string galeryName = ui->galeriaText->text().toUtf8().constData();


        //CAMBIAR METODO CON DAVID
        std::string ipAdress = "192.168.100.9", port = "9080";
        Requests *requests = new Requests(ipAdress, port);

        Parser *parser = new Parser();
        json answer;
        answer["table"] = galeryName;
        if (!answer.empty()) {
            std::string enviar = answer.dump();
            std::cout << enviar << std::endl;
            requests->sendPostRequest(enviar, CREATE); //cambiar CREATE?
        }
        updated = false;
        //mandar metadata
        close();
    }else{
        QMessageBox::critical(this,tr("ERROR"),tr("Falta dato")); //ventana emergente
    }
}

QString newphoto:: getNombre(){
    return ui->nombreText->text();
}
QString newphoto:: getAutor(){
    return ui->autorText->text();
}
QString newphoto:: getAno(){
    return ui->anoText->text();
}
QString newphoto:: getTamano(){
    return ui->tamanoText->text();
}
QString newphoto:: getDescrip(){
    return ui->descripcionText->text();
}
QString newphoto:: getGalery(){
    return ui->galeriaText->text();
}
