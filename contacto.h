#ifndef CONTACTO_H
#define CONTACTO_H

#include <QString>

class Contacto
{
private:
    QString userName, phoneNumber;

public:
    Contacto();
    Contacto(const QString &name, const QString phone);

    //GETTER AND SETTER
    QString getUserName() const;
    void setUserName(const QString &value);

    QString getPhoneNumber() const;
    void setPhoneNumber(const QString &value);

};

#endif // CONTACTO_H
