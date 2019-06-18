#include "scriptwindow.h"
#include "ui_scriptwindow.h"
#include <mainwindow.h>
#include "boost/algorithm/string.hpp"

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

/**
 * boton para agregar nueva metada por medio de scripts, usando la sintaxis de SQL
 */
void scriptwindow::on_doneButton_clicked()
{
    QString allText = ui->plainTextEdit->toPlainText();
    QString fWords = allText.mid(0,6); //get first 6 letter from string
    std::string utf8_text = allText.toUtf8().constData(); //QString to string

    std::string ipAdress = "192.168.100.2", port = "9080";
    Requests *requests = new Requests(ipAdress, port);
    std::string answer;
    if(fWords == "INSERT"){
        Parser *parser = new Parser();
        //std::string prueba = "INSERT INTO vacaciones (lugar,tiempo) VALUES (portland,2años)";
        //std::string prueba = "SELECT (lugar,tiempo) FROM vacaciones WHERE CACA in (MIERDA,PEDO)"; "SELECT (name,author,year,size,description) FROM galery WHERE ";
        //std::string prueba = "DELETE FROM vacaciones WHERE lugar=portland";
        //std::string prueba = "DELETE FROM vacaciones";
        //std::string prueba = "UPDATE vacaciones SET lugar=portland,author=david,year=2017 WHERE descripcion=hola";


        QString filename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                    "Image (*.jpeg)"
                    );
        qDebug()<<filename;
        std::string filenameString = filename.toUtf8().constData();
        vector<string> input;
        boost::split(input,filenameString, boost::is_any_of("."));
        std::string ext = input.at(1);

        QString shit = QString::fromStdString(ext);
        qDebug()<<shit;

        //METADATA METODO DE CAMACHO
        std::ifstream ifs(filenameString, std::ios::binary|std::ios::ate);
        std::ifstream::pos_type pos = ifs.tellg();
        char* buffer = new char[pos];
        ifs.seekg(0, std::ios::beg);
        ifs.read(buffer, pos);
        std::vector<char> data(buffer, buffer+int(pos));
        std::string out(data.begin(), data.end());


        QString qstr = QString::fromStdString(out);
        qDebug()<<qstr;

        json respuestaScript = parser->scriptTypeofRequestParser(utf8_text);
        std::string temp = respuestaScript.dump();
        if (!respuestaScript.empty()) {

            std::string answer = requests->sendPostRequest(temp, INSERT);
            json meta = json::parse(answer);
            std::string name = meta["id"];
            std::string ext = meta["ext"];


            if (answer != "false") {
                std::ostringstream os;
                os << name.size() << name << "." << ext;
                std::string final = os.str();
                std::string answer2 = requests->sendPostRequest(final, IMAGE);
            }
        }
        updated = false;
        close();
    }else{

        close();

        if(fWords == "SELECT"){
            Parser *parser = new Parser();
            json respuesta = parser->scriptTypeofRequestParser(utf8_text);
            std::cout << respuesta.dump() << std::endl;
            if (!respuesta.empty()) {
                std::string enviar = respuesta.dump();
                std::cout << enviar << std::endl;
                image = requests->sendPostRequest(enviar, SELECT);
            }
            MainWindow mw;
            //mw.loadPhoto(image);
            //recibir jason de david con los bits de la imagen


            char *act1 = new char[image.size()];
            strncpy(act1, image.c_str(), image.size());
            close();
        }else{
            if(fWords == "UPDATE"){
                Parser *parser = new Parser();
                json respuesta = parser->scriptTypeofRequestParser(utf8_text);
                if (!respuesta.empty()) {
                    std::string enviar = respuesta.dump();
                    std::cout << enviar << std::endl;
                    requests->sendPostRequest(enviar, UPDATE);
                }
                updated = false;
                close();
            }else{

                if(fWords == "DELETE"){
                    Parser *parser = new Parser();
                    json respuesta = parser->scriptTypeofRequestParser(utf8_text);
                    if (!respuesta.empty()) {
                        std::string enviar = respuesta.dump();
                        std::cout << enviar << std::endl;
                        requests->sendPostRequest(enviar, DELETE);
                    }
                    close();
                    updated = false;
                }else{
                    QMessageBox::critical(this,tr("ERROR"),tr("Ingresar un sintaxis correcta"));
                    ui->plainTextEdit->clear();
                }
            }
        }
    }
}
