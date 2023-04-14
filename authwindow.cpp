#include "authwindow.h"
#include "ui_authwindow.h"
#include "user.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "studentform.h"
#include "librarianform.h"

AuthWindow::AuthWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_loginButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
//    User newUser = User(login, password, "admin");
    User* user = User::find_user(login, password);


    //Проверка пароля и логина
    if (user){
        if (user->get_type() == "Admin"){
           QMessageBox::information(this, "Добро Пожаловать!", "Вы - Администратор");
           MainWindow *mainWindow = new MainWindow(this);
           mainWindow->show();
           mainWindow->showAdminForm();
           this->hide();
           // TODO
        } else if (user->get_type() == "Student"){
            QMessageBox::information(this, "Добро Пожаловать!", "Вы - Студент");
            Studentform *studform = new Studentform(this);
            studform->show();
            this->hide();
            // TODO
        } else if (user->get_type() == "Librarian"){
            QMessageBox::information(this, "Добро Пожаловать!", "Вы - Библеотекарь");
            Librarianform *Libform = new Librarianform(this);
            Libform->show();
            this->hide();
            // TODO
        } else if (user->get_type() == "User"){
            QMessageBox::information(this, "Добро Пожаловать!", "Вы - Гость");
         }

    } else {
        QMessageBox::warning(this, "Упс", "Неудачная попытка входа");
    }
}
