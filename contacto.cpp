#include "contacto.h"

Contacto::Contacto()
{
    userName = "Unknown";
    phoneNumber = "Unknown";
}

Contacto::Contacto(const QString &name, const QString phone)
{
    userName = name;
    phoneNumber = phone;
}

QString Contacto::getUserName() const
{
    return  userName;
}

void Contacto::setUserName(const QString &value)
{
    userName = value;
}

QString Contacto::getPhoneNumber() const
{
    return  phoneNumber;
}

void Contacto::setPhoneNumber(const QString &value)
{
    phoneNumber = value;
}
