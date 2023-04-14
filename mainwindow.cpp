#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "documentation.h"
#include "authors.h"
#include "adminform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authFormButton_clicked()
{
    hide();
    authWindow = new AuthWindow(this);
    authWindow->show();
}

void MainWindow::showAdminForm()
{
    hide();
    adminWindow = new AdminForm(this);
    adminWindow->show();
}

void MainWindow::on_DocButton_clicked()
{
    Documentation Docum;
    Docum.setModal(true);
    Docum.exec();
}


void MainWindow::on_InfAuthorButton_clicked()
{
    Authors Author;
    Author.setModal(true);
    Author.exec();
}

