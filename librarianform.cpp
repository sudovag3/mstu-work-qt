#include "book.h"
#include "librarianform.h"
#include "ui_librarianform.h"
#include "authwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QPushButton>
#include <QString>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QPointer>

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
    this->hide();
}


void Librarianform::on_Downloadimage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename, QString()) !=0){
        QImage image;
        bool valid = image.load(filename);

        if(valid){
          image = image.scaledToWidth( ui->Lbl_image->width(), Qt::SmoothTransformation);
          image = image.scaledToHeight( ui->Lbl_image->height(), Qt::SmoothTransformation);
          ui->Lbl_image->setPixmap(QPixmap::fromImage(image));
        }
        else {
            QMessageBox::information(this, tr("Ошибка"),
                                     tr("Обложка не загруженна!"));
        }
    }
}
