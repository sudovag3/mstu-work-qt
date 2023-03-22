#include "admin.h"

// Конструктор класса Admin
Admin::Admin(const QString& login, const QString& password)
    : User(login, password) {
    user_type_ = "admin";
}

// Функция получения типа пользователя
QString Admin::get_type() const {
    return "Admin";
}
