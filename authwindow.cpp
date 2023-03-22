#include "authwindow.h"
#include "ui_authwindow.h"
#include <QMessageBox>

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

    //Проверка пароля и логина
    if (login == "Test"){

    } else {
        QMessageBox::warning(this, "Упс", "Неудачная попытка входа");
    }
}
