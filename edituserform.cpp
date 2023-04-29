#include "edituserform.h"
#include "ui_edituserform.h"

EditUserForm::EditUserForm(User *user, QWidget *parent)
    : QDialog(parent), user_(user), ui(new Ui::EditUserForm) {
    ui->setupUi(this);
    connect(ui->editUserButton, &QPushButton::clicked, this, &EditUserForm::on_editUserButton_clicked);
    // Заполняем поля формы текущими значениями пользователя
    ui->editLogin->setText(user_->get_login());
    ui->editPassword->setText(""); // Оставляем поле пароля пустым
    QString userType = user_->get_type();
    if (userType == "student") {
        ui->radioStudent->setChecked(true);
    } else if (userType == "librarian") {
        ui->radioLibrarian->setChecked(true);
    } else if (userType == "admin") {
        ui->radioAdmin->setChecked(true);
    }
}

EditUserForm::~EditUserForm()
{
    delete ui;
}

void EditUserForm::on_editUserButton_clicked() {
    // Сохраняем измененные данные пользователя
    user_->set_login(ui->editLogin->text());

    // Задаем новый пароль только если поле пароля не пусто
    if (!ui->editPassword->text().isEmpty()) {
        user_->set_password(ui->editPassword->text());
    }

    QString userType;
    if (ui->radioStudent->isChecked()) {
        userType = "student";
    } else if (ui->radioLibrarian->isChecked()) {
        userType = "librarian";
    } else if (ui->radioAdmin->isChecked()) {
        userType = "admin";
    }
    user_->set_type(userType);


    // Вызываем сигнал, что пользователь был изменен
    emit userEdited();
}
