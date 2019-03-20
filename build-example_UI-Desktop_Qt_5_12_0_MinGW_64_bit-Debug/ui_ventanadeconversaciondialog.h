/********************************************************************************
** Form generated from reading UI file 'ventanadeconversaciondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANADECONVERSACIONDIALOG_H
#define UI_VENTANADECONVERSACIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_VentanadeConversacionDialog
{
public:
    QLineEdit *chatLineEdit;
    QTableWidget *VentanatableWidget;
    QPushButton *EnviarpushButton;
    QLineEdit *MensajelineEdit;

    void setupUi(QDialog *VentanadeConversacionDialog)
    {
        if (VentanadeConversacionDialog->objectName().isEmpty())
            VentanadeConversacionDialog->setObjectName(QString::fromUtf8("VentanadeConversacionDialog"));
        VentanadeConversacionDialog->resize(400, 300);
        chatLineEdit = new QLineEdit(VentanadeConversacionDialog);
        chatLineEdit->setObjectName(QString::fromUtf8("chatLineEdit"));
        chatLineEdit->setGeometry(QRect(10, 9, 381, 21));
        chatLineEdit->setLayoutDirection(Qt::LeftToRight);
        chatLineEdit->setAlignment(Qt::AlignCenter);
        VentanatableWidget = new QTableWidget(VentanadeConversacionDialog);
        VentanatableWidget->setObjectName(QString::fromUtf8("VentanatableWidget"));
        VentanatableWidget->setGeometry(QRect(10, 40, 381, 201));
        EnviarpushButton = new QPushButton(VentanadeConversacionDialog);
        EnviarpushButton->setObjectName(QString::fromUtf8("EnviarpushButton"));
        EnviarpushButton->setGeometry(QRect(300, 250, 81, 41));
        MensajelineEdit = new QLineEdit(VentanadeConversacionDialog);
        MensajelineEdit->setObjectName(QString::fromUtf8("MensajelineEdit"));
        MensajelineEdit->setGeometry(QRect(10, 250, 281, 41));

        retranslateUi(VentanadeConversacionDialog);

        QMetaObject::connectSlotsByName(VentanadeConversacionDialog);
    } // setupUi

    void retranslateUi(QDialog *VentanadeConversacionDialog)
    {
        VentanadeConversacionDialog->setWindowTitle(QApplication::translate("VentanadeConversacionDialog", "Dialog", nullptr));
        chatLineEdit->setText(QApplication::translate("VentanadeConversacionDialog", "Chat", nullptr));
        EnviarpushButton->setText(QApplication::translate("VentanadeConversacionDialog", "Enviar!!", nullptr));
        MensajelineEdit->setPlaceholderText(QApplication::translate("VentanadeConversacionDialog", "Ingresa el mensaje que deseas enviar. ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VentanadeConversacionDialog: public Ui_VentanadeConversacionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANADECONVERSACIONDIALOG_H
