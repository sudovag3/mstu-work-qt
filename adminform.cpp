#include "adminform.h"
#include "ui_adminform.h"
#include "user.h"
#include "user_find.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QPushButton>
#include <QString>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMessageBox>


AdminForm::AdminForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi(this);
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
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->setAlignment(Qt::AlignVCenter);
//        layout->addWidget(edit_button);
//        layout->addWidget(delete_button);
//        QWidget* widget = new QWidget(ui->userListWidget);
//        widget->setLayout(layout);
//        widget->setContentsMargins(0, 0, 0, 0);
//        ui->userListWidget->setItemWidget(item, widget);
//        ui->userListWidget->addItem(item);

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

        // Подключаем обработчики нажатия на кнопки
        connect(editButton, &QPushButton::clicked, [=]() {
            // TODO: Реализовать обработчик нажатия на кнопку "Редактировать"
            // Необходимо открыть форму редактирования пользователя, передав ей указатель на объект пользователя
            // и обработать изменения в файле users.json
            // Возможно, стоит использовать сигналы и слоты для обновления списка пользователей на главном окне
        });

        connect(deleteButton, &QPushButton::clicked, [=]() {
            // TODO: Реализовать обработчик нажатия на кнопку "Удалить"
            // Необходимо удалить объект пользователя и обновить данные в файле users.json
            // Возможно, стоит использовать сигналы и слоты для обновления списка пользователей на главном окне
        });
    }

    for (User* user : users_list) {
        delete user;
    }

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
}
