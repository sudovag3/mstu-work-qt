#include "studentform.h"
#include "ui_studentform.h"
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
    this->hide();
}
/*
void Studentform::update_Bibl_list() {
    ui->BibllistWidget->clear(); // Очищаем список книг библиотеки
    QListWidgetItem* item = new QListWidgetItem(ui->BibllistWidget);
    item->setSizeHint(QSize(0, 40)); // Задаем фиксированную высоту для строки списка
    item->setTextAlignment(Qt::AlignVCenter); // Выравнивание текста по вертикальному центру

    // Создаем виджет с информацией о пользователе
    QWidget* BiblWidget = new QWidget(ui->BibllistWidget);
    QVBoxLayout* BiblLayout = new QVBoxLayout(BiblWidget);
    QLabel* BiblInfoLabel = new QLabel(Bibl_info);
    BiblLayout->addWidget(BiblInfoLabel);

    // Создаем виджет с кнопками
    QWidget* buttonWidget = new QWidget(ui->BibllistWidget);
    QGridLayout* buttonLayout = new QGridLayout(buttonWidget);
    QPushButton* VzyatButton = new QPushButton("Взять");
    buttonLayout->addWidget(editButton, 0, 0);

    // Добавляем виджеты к элементу списка
    BiblLayout->addWidget(buttonWidget);
    item->setSizeHint(BiblWidget->sizeHint());
    ui->BibllistWidget->setItemWidget(item, BiblWidget);

    connect(VzyatButton, &QPushButton::clicked, [=]() {

        editUserForm->open();
    });
}*/
