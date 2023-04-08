#include "librarianform.h"
#include "ui_librarianform.h"
#include "authwindow.h"

Librarianform::Librarianform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Librarianform)
{
    ui->setupUi(this);
}

Librarianform::~Librarianform()
{
    delete ui;
}

void Librarianform::on_ButtonClose_clicked()
{
    AuthWindow *authwind = new AuthWindow(this);
    authwind->show();
    this->close();
}

