#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "documentation.h"
#include "authors.h"
#include "adminform.h"
#include <QDesktopServices>
#include <QUrl>


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
    QDesktopServices::openUrl(QUrl::fromUserInput("https://talented-gaura-042.notion.site/f9a6b4cf7c934eb7a9cfc40da01619f4?pvs=4"));
}


void MainWindow::on_InfAuthorButton_clicked()
{
    Authors Author;
    Author.setModal(true);
    Author.exec();
}


void MainWindow::on_reviewFormButton_clicked()
{
    QDesktopServices::openUrl(QUrl::fromUserInput("https://formdesigner.ru/form/view/199816"));
}
