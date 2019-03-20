#include "ventanadeconversaciondialog.h"
#include "ui_ventanadeconversaciondialog.h"
//Constructor
VentanadeConversacionDialog::VentanadeConversacionDialog(QString users, QString contacto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanadeConversacionDialog)
{
    ui->setupUi(this);
    ///Nombre es el equivalente a userName de contaco y usuario...
    Nombre = users;
    ///Es similar al userName, pero en la parte de contactos...
    Contacto = contacto;
    system("mkdir colormensaje");

   //ui->EnviarpushButton->setStyleSheet("background-color: #");

    //Archivo();
    //loadFile();
    ///actualizacionDeConversacion();
}
//Destructor
VentanadeConversacionDialog::~VentanadeConversacionDialog()
{
    delete ui;
}
///Es el boton para después de escribir el mensaje y enviarlo.
void VentanadeConversacionDialog::on_EnviarpushButton_clicked()
{
    Conversacion newMessage(Nombre, ui->MensajelineEdit->text());
    mensaje.push_back(newMessage);

    QJsonObject mensajeQJsonOb;
    mensajeQJsonOb["Transmicion"]= newMessage.getTrans();
    mensajeQJsonOb["Texto"]= newMessage.getTexto();
    mensajeQJsonOb["Fecha"]= newMessage.getFecha();
    ///QJsonArray
    MensajeJson.append(mensajeQJsonOb);

    //saveFile();
    //actualizacionDeConversacion();

    ui->MensajelineEdit->setText("");
}
///Es para los mensajes de texto que se enviarán los if y else espara poner el color a los recuadros de conversacion y dependiendo de quien sea
/// la persona que envia o recibe, es el color que se obtendrá en su recuadro.
void VentanadeConversacionDialog::on_MensajelineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

     ///usuario que envía el mensaje.
    if(validacionDeCadena(ui->MensajelineEdit->text())==true)
    {

        ui->EnviarpushButton->setEnabled(true);
       // ui->EnviarpushButton->setStyleSheet("background-color:#");
    }
    else {///Usuario que ve el mensaje recibido
        ui->EnviarpushButton->setEnabled(false);
        //ui->EnviarpushButton->setStyleSheet("background-color:#");
    }
}

///void VentanadeConversacionDialog::Archivo()
//{
  //  if(Nombre >Contacto)

//}

//void VentanadeConversacionDialog::loadFile()
//{

//}

//void VentanadeConversacionDialog::saveFile()
//{

//}

bool VentanadeConversacionDialog::validacionDeCadena(QString Texto)
{
    ///Validaremos los estring para esto utilizaremos un if y dentro de este if viene un for
    /// Lo cual nso verifica si es un string valido y que no tenga espacios en blanco.
    if(Texto.length()== 0)
        return false;
    for(int m = 0; m < Texto.length(); m++)
    {
        if (Texto[m] != ' ')
            return true;
    }
    return false;
}
