#include "adminform.h"
#include "ui_adminform.h"
#include "user.h"
#include "user_find.h"
#include "authwindow.h"
#include "edituserform.h"
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


AdminForm::AdminForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi(this);
    update_user_list();


}

void AdminForm::update_user_list() {
    ui->userListWidget->clear(); // Очищаем список пользователей

    QList<User*> users_list = read_users_from_file();
    for (User* user : users_list) {
        QString user_info = QString("Логин: %1, Пароль: %2, Тип: %3")
                        .arg(user->get_login())
                        .arg(user->get_password())
                        .arg(user->get_type());
        QListWidgetItem* item = new QListWidgetItem(ui->userListWidget);
        item->setSizeHint(QSize(0, 40)); // Задаем фиксированную высоту для строки списка
        item->setTextAlignment(Qt::AlignVCenter); // Выравнивание текста по вертикальному центру

        // Создаем виджет с информацией о пользователе
        QWidget* userWidget = new QWidget(ui->userListWidget);
        QVBoxLayout* userLayout = new QVBoxLayout(userWidget);
        QLabel* userInfoLabel = new QLabel(user_info);
        userLayout->addWidget(userInfoLabel);

        // Создаем виджет с кнопками
        QWidget* buttonWidget = new QWidget(ui->userListWidget);
        QGridLayout* buttonLayout = new QGridLayout(buttonWidget);
        QPushButton* editButton = new QPushButton("Редактировать");
        QPushButton* deleteButton = new QPushButton("Удалить");
        buttonLayout->addWidget(editButton, 0, 0);
        buttonLayout->addWidget(deleteButton, 0, 1);

        // Добавляем виджеты к элементу списка
        userLayout->addWidget(buttonWidget);
        item->setSizeHint(userWidget->sizeHint());
        ui->userListWidget->setItemWidget(item, userWidget);

        connect(editButton, &QPushButton::clicked, [=]() {
            // Создаем и показываем форму редактирования пользователя
            EditUserForm *editUserForm = new EditUserForm(user);
            editUserForm->setAttribute(Qt::WA_DeleteOnClose);
            connect(editUserForm, &EditUserForm::userEdited, this, &AdminForm::on_userEdited);
            editUserForm->open();
        });

        connect(deleteButton, &QPushButton::clicked, [=]() {
            // Удаляем пользователя из файла
            User::delete_user_from_file(user->get_login());

            // Удаляем пользователя из списка пользователей
            delete user;
            delete item;

            // Вызываем сигнал, что пользователь был удален
            emit userDeleted();
            update_user_list();
        });
    }

//    for (User* user : users_list) {
//        delete user;
//    }
}


void AdminForm::on_userEdited() {
    // Обновляем список пользователей
    QMessageBox::information(this, tr("Успешно"),
                             tr("Пользователь отредактирован успешно!"));
    update_user_list();
}

AdminForm::~AdminForm()
{
    delete ui;
}

void AdminForm::on_createUserButton_clicked()
{
    QString login = ui->createLogin->text();
    QString password = ui->createPassword->text();
    QString userType;
    if (ui->radioStudent->isChecked()) {
        userType = "student";
    } else if (ui->radioLibrarian->isChecked()) {
        userType = "librarian";
    } else if (ui->radioAdmin->isChecked()) {
        userType = "admin";
    }

    // Создаем нового пользователя
    User newUser = User(login, password, userType);

    // Оповещаем пользователя об успешном создании
    QMessageBox::information(this, tr("Успешно"),
                             tr("Пользователь создан успешно!"));

    // Очищаем поля ввода
    ui->createLogin->clear();
    ui->createPassword->clear();
    update_user_list();
}

void AdminForm::on_ButtonClose_clicked()
{
    AuthWindow *authwind = new AuthWindow(this);
    authwind->show();
    this->close();
}

