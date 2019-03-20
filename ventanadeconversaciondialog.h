#ifndef VENTANADECONVERSACIONDIALOG_H
#define VENTANADECONVERSACIONDIALOG_H

#include "colormensaje.h"
#include "conversacion.h"

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHBoxLayout>

////Holis señor Christian, este archivo es el más importante de la conversacion
namespace Ui {
class VentanadeConversacionDialog;
}

class VentanadeConversacionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VentanadeConversacionDialog(QString users, QString contacto, QWidget *parent = nullptr);
    ~VentanadeConversacionDialog();

private slots:
    void on_EnviarpushButton_clicked();

    void on_MensajelineEdit_textChanged(const QString &arg1);

private:
    Ui::VentanadeConversacionDialog *ui;
    QString Nombre;
    QString Contacto;

    std::vector<Conversacion>mensaje;
    QFile Mensaje;
    QJsonArray MensajeJson;

  /*  void Archivo();
    void loadFile();
    void saveFile();*/

    bool validacionDeCadena(QString Texto);
    //void actualizacionDeConversacion();

};

#endif // VENTANADECONVERSACIONDIALOG_H
