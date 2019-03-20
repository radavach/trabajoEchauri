#include "colormensaje.h"
#include "ui_colormensaje.h"


///Es para el color del mensaje
/// Constructor
ColorMensaje::ColorMensaje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorMensaje)
{
    ui->setupUi(this);
}
///Destructor
ColorMensaje::~ColorMensaje()
{
    delete ui;
}

void ColorMensaje::setText(QString text)
{
    ui->TextoMensajetextEdit->setText(text);
}

void ColorMensaje::setFecha(QString fech)
{
    ui->Fecha->setText(fech);
}

void ColorMensaje::setColores(QString color)
{
    this->setStyleSheet("QDialog{border-radius:15px; border-style:none; background-color:" + color + "}");
}
