#include "admin.h"

// Конструктор класса Admin
Admin::Admin(const QString& login, const QString& password)
    : User(login, password, "admin") {
}


Admin::Admin(const QString& login, const QString& password, bool is_hashed)
    : User(login, password, "admin", is_hashed) {
}


// Функция получения типа пользователя
QString Admin::get_type() const {
    return "Admin";
}
