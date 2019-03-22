#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(User *u, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    user = u;

    usersdb.setFileName("DB.json"); //Asignar nombre al archivo
    contactsdb.setFileName("contactsOf_" + user->getUserName() + ".json" ); //Asignar nombre al archivo

    loadUsers();
    //loadContacts();

    updateContactList();
    updateUsersList();
}

MainWindow::~MainWindow()
{
    //saveContacts();
    saveUsers();
    delete ui;
}


// WIDGETS:
void MainWindow::on_ProfileCheckBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->ProfileButton->setEnabled(true);
}

void MainWindow::on_ProfileButton_clicked()
{
    QMessageBox message;

    message.setWindowTitle("Profile");
    message.setText(
        "User: " + user->getUserName() +
        "\nPassword: " + user->getPassword() +
        "\nPhone: " + user->getPhoneNumber() + "\n"
    );
    message.exec();
}

//void MainWindow::on_ShowAllButton_clicked()
//{
    //updateUsersList();
//}

void MainWindow::on_BusquedaLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    if(ui->BusquedaLineEdit->text().length() > 0){
        ui->BuscarButton->setEnabled(true);
    }

    else{
        ui->BuscarButton->setEnabled(false);
    }
}

void MainWindow::on_AddLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    if(ui->AddLineEdit->text().length() > 0){
        ui->AddButton->setEnabled(true);
    }

    else{
        ui->AddButton->setEnabled(false);
    }
}

void MainWindow::on_LogOutButton_clicked()
{
    //saveContacts();
    saveUsers();
    this->close();
}

//FUNCIONES:

void MainWindow::loadUsers()
{
    if(!usersdb.open(QIODevice::ReadOnly)){
        QMessageBox message;
        message.setWindowTitle("Error");
        message.setText("No se pudo abrir la base de datos");
        message.exec();
    }

    else{
        QByteArray data = usersdb.readAll();
        QJsonDocument jsonDocument(QJsonDocument::fromJson(data)); //DESFORMATEAR
        QJsonObject jsonObject = jsonDocument.object();
        usersJsonArray = jsonObject["users"].toArray();

        for(int i=0; i < usersJsonArray.size(); ++i){
            QJsonObject obj = usersJsonArray[i].toObject();
            User u;

            u.setUserName(obj["name"].toString());
            u.setPhoneNumber(obj["phone"].toString());
            u.setPassword(obj["password"].toString());


            ///Para leer la lista de contactos
            /// se convierte en array
            QJsonArray jsonArrayContactos = obj["contactos"].toArray();
            Contacto contactos;
            for(int j=0; j < jsonArrayContactos.size(); j++)
            {
                QJsonObject objCont = jsonArrayContactos[j].toObject();
                contactos.setUserName(objCont["name"].toString());
                contactos.setPhoneNumber(objCont["phone"].toString());

                QJsonArray jsonArrayMensaje = objCont["mensajes"].toArray();
                Conversacion conversacion;

                ///Lo siguiente que se hará es ... No recuerdo, lo siento !!!!!! :(
                for(int m= 0; m <jsonArrayMensaje.size(); m++)
                {
                    QJsonObject objMensaje = jsonArrayMensaje[m].toObject();
                    conversacion.setFecha(objMensaje["fecha"].toString());
                    conversacion.setTexto(objMensaje["texto"].toString());
                    conversacion.setTrans(objMensaje["transmicion"].toString());

                    contactos.addMensaje(conversacion);
                }

                u.addContact(contactos);
            }

            usersVector.push_back(u);
        }
    }

    usersdb.close();
}

void MainWindow::saveUsers()
{

    QJsonArray jsonArrayUsuarios;
    QJsonObject jsonObject;
    for(unsigned int i=0; i < usersVector.size(); i++)
    {
        QJsonObject jsonObjectUsuario, jsonObjectContacto;
        QJsonArray jsonarrayContactos;
        std::vector<Contacto> contactos;

        jsonObjectUsuario["name"] = usersVector[i].getUserName();
        jsonObjectUsuario["password"] = usersVector[i].getPassword();
        jsonObjectUsuario["phone"] = usersVector[i].getPhoneNumber();

        contactos = (usersVector[i].getUserName() == user->getUserName())? user->getContactos():usersVector[i].getContactos();


        for(unsigned int j=0; j < contactos.size(); j++)
        {

            jsonObjectContacto["name"] = contactos[j].getUserName();
            jsonObjectContacto["phone"] = contactos[j].getPhoneNumber();




            jsonarrayContactos.append(jsonObjectContacto);
        }
        jsonObjectUsuario["contactos"] = jsonarrayContactos;

        jsonArrayUsuarios.append(jsonObjectUsuario);

    }

    saveDB(jsonArrayUsuarios);

}


bool MainWindow::isMyContact(QString userName)
{
    if(user->getUserName() == userName)
        return true;

    if(user->getContactos().size() == 0)
        return false;

    else{

        for(unsigned int i = 0; i < user->getContactos().size() ; i++ ){
            if(user->getContactos()[i].getUserName() == userName)
                return true;
        }
        return false;
    }
}

bool MainWindow::isAnUser(QString userName)
{
    if(usersVector.size() == 0)
        return false;
    else{
        for(unsigned int i = 0; i < usersVector.size(); i++){
            if(usersVector[i].getUserName() == userName)
                return true;
        }
    }
    return false;
}

void MainWindow::updateContactList()
{
    if(user->getContactos().size() == 0)
        ui->ContactsTextEdit->setText("No hay contactos en la lista");

    else{
        QString contactsList = "";

        for(unsigned int i = 0; i < user->getContactos().size(); i++){
            contactsList+= user->getContactos()[i].getUserName() + "\n";
        }

        ui->ContactsTextEdit->setText(contactsList);
    }
}

void MainWindow::updateUsersList()
{
    if(usersVector.size() == 0){
        ui->UsersTextEdit->setText("No hay nada para mostrar");
    }

    else{
        QString usersList = "";

        for(unsigned int i = 0; i < usersVector.size(); i++){

            if(isMyContact( usersVector[i].getUserName() ) == false ){
                usersList+= usersVector[i].getUserName() + " : [" + usersVector[i].getPhoneNumber() + "]\n";
            }
        }

        ui->UsersTextEdit->setText(usersList);
    }
}

QString MainWindow::getPhoneByUser(QString username)
{
    for(unsigned int i = 0; i < usersVector.size(); i++){

        if(usersVector[i].getUserName() == username)
            return usersVector[i].getPhoneNumber();
    }
    return "Unknown";
}

void MainWindow::searchUsersByName(QString name)
{

    QString searchList = "Results: \n\n";

    for(unsigned int i = 0; i < usersVector.size(); i++){   //se recorre la lista de usuarios

        QString thisUser = usersVector[i].getUserName();

        for(int n = 0; n < thisUser.length(); n++){ //se recorre ahora los nombres de los usuarios

            if(thisUser[n] == name[0]){

                //Longitud de nombre - lugar >= name
                if( (thisUser.length() - n) >= name.length() ){   //Comprueba si hay espacio

                    bool sonIguales = true;

                    for(int x = 0; x < name.length(); x++){

                        if(thisUser[n+x] != name[x]){
                            sonIguales = false;
                        }
                    }

                    if(sonIguales){ //SI TIENE MI CONDICION
                        if(isMyContact(thisUser) == false){ //SI NO ES MI CONTACTO
                            searchList+= thisUser + "\n";
                        }
                    }
                }
            }
        }
    }

    ui->UsersTextEdit->setText(searchList);
}

void MainWindow::on_AddButton_clicked()
{
    QMessageBox msn;

    if (ui->AddLineEdit->text() == user->getUserName()){    //ES MI NOMBRE
        msn.setWindowTitle("Tu nombre");
        msn.setText("No te puedes añadir");
    }
    else{
        if(!isAnUser(ui->AddLineEdit->text())){ //NO ES UN USUARIO
            msn.setWindowTitle("Usuario no existente");
            msn.setText("No se ha llamado a nadie" + ui->AddLineEdit->text());
        }

        else{
            if(isMyContact(ui->AddLineEdit->text())){   //YA ES MI CONTACTO
                msn.setWindowTitle("Es tu contacto");
                msn.setText(ui->AddLineEdit->text() + " ya existe en tus contactos");
            }
            else{   //PUEDO AGREGARLO

                QString phone = getPhoneByUser(ui->AddLineEdit->text());
                Contacto newContact(ui->AddLineEdit->text(), phone);

                user->addContact(newContact); ///AGREGAR AL VECTOR

                QJsonObject contactJsonObject;
                contactJsonObject["name"] = newContact.getUserName();
                contactJsonObject["phone"] = newContact.getPhoneNumber();

                contactsJsonArray.append(contactJsonObject);   //AGREGAR AL OBJETO JSON

                msn.setWindowTitle("Nuevo usuario");
                msn.setText(ui->AddLineEdit->text() + " a sido agregado a tus contactos");


            }
        }
    }
    msn.exec();

    updateContactList();    //ACTUALIZA CONTACTS
    updateUsersList();      //ACTUALIZA USERS
    saveUsers();


    //saveContacts();         //GUARDA
}

void MainWindow::on_BuscarButton_clicked()
{
    //Buscar:
    searchUsersByName(ui->BusquedaLineEdit->text());
}

void MainWindow::on_EnviarpushButton_clicked()
{
}

//Es una funcion que manda a guardar el JSon usuarios
void MainWindow::saveDB(QJsonArray jsonArray)
{
    emit saveUs(jsonArray);
}
