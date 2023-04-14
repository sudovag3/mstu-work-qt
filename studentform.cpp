#include "studentform.h"
#include "ui_studentform.h"
#include "authwindow.h"

Studentform::Studentform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Studentform)
{
    ui->setupUi(this);
}

Studentform::~Studentform()
{
    delete ui;
}

void Studentform::on_Vihod_clicked()
{
    AuthWindow *authwind = new AuthWindow(this);
    authwind->show();
    this->close();
}

