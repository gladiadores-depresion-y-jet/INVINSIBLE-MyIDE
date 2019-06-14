#include "newphoto.h"
#include "ui_newphoto.h"


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

void newphoto::on_ImagenBoton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Image (*.jpeg)"
                ); //opens .jpeg files only
    QPixmap pix(filename);
    std::string filenameString = filename.toUtf8().constData();

    ui->fotolabel->setPixmap(pix.scaled(350,350,Qt::KeepAspectRatio));

    //METADATA
    std::ifstream ifs(filenameString, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    char* buffer = new char[pos];
    ifs.seekg(0, std::ios::beg);
    ifs.read(buffer, pos);
    std::vector<char> data(buffer, buffer+int(pos));
    //pasar data a camacho

}

void newphoto::on_doneBoton_clicked()
{
    if(ui->nombreText->text() != "" && ui->autorText->text() != "" && ui->anoText->text() != "" && ui->tamanoText->text() != "" && ui->descripcionText->text() != "" && ui->galeriaText->text() != ""){
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
