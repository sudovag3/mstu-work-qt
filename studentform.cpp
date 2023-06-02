#include "studentform.h"
#include "user.h"
#include "ui_studentform.h"
#include "authwindow.h"
#include "studentbook.h"

#include <QString>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

#include <QList>
#include <QPushButton>
#include <QString>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QPointer>
#include <QGridLayout>


Studentform::Studentform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Studentform)
{
    ui->setupUi(this);
    update_student();
}

Studentform::~Studentform()
{
    delete ui;
}

void Studentform::update_student()
{

    ui->BooklistWidget->clear(); // Очищаем список взятых книг
    QFile file("studentbooks.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if(docError.errorString().toInt()==QJsonParseError::NoError) {
        docAr = QJsonValue(doc.object().value(login)).toArray(); // выводим данные авторизованного студента

        for (int i = 0; i < docAr.count(); i++) {

            QString Idd_Book = docAr.at(i).toObject().value("Idd_Book").toString(); //получаем Idd_Book


            QString book_info = QString("Idd_Book: %1").arg(Idd_Book);


            QListWidgetItem* item = new QListWidgetItem(ui->BooklistWidget);
            item->setSizeHint(QSize(0, 40)); // Задаем фиксированную высоту для строки списка
            item->setTextAlignment(Qt::AlignVCenter); // Выравнивание текста по вертикальному центру

            // Создаем виджет с информацией о пользователе
            QWidget* bookWidget = new QWidget(ui->BooklistWidget);
            QVBoxLayout* bookLayout = new QVBoxLayout(bookWidget);
            QLabel* bookInfoLabel = new QLabel(book_info);
            bookLayout->addWidget(bookInfoLabel);

            // Создаем виджет с кнопками
            QWidget* buttonWidget = new QWidget(ui->BooklistWidget);
            QGridLayout* buttonLayout = new QGridLayout(buttonWidget);
            QPushButton* prosmotrButton = new QPushButton("Просмотр");
            QPushButton* returnButton = new QPushButton("Вернуть");
            buttonLayout->addWidget(prosmotrButton, 0, 0);
            buttonLayout->addWidget(returnButton, 0, 1);

            // Добавляем виджеты к элементу списка
            bookLayout->addWidget(buttonWidget);
            item->setSizeHint(bookWidget->sizeHint());
            ui->BooklistWidget->setItemWidget(item, bookWidget);
        }
    }
    
}

void Studentform::on_Vihod_clicked()
{
    AuthWindow *authwind = new AuthWindow(this);
    authwind->show();
    this->hide();
}

void Studentform::on_AddButton_clicked()
{
    QString book; // Idd книги

    update_student();
   // StudentBook(login,book); // берем книгу из библиотеки
}

