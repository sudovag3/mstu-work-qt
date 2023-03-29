#include "mainwindow.h"
#include "ui_mainwindow.h"
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
