#include "librarian.h"

// Конструктор класса Librarian
Librarian::Librarian(const QString& login, const QString& password)
    : User(login, password, "librarian") {
}

// Функция получения типа пользователя
QString Librarian::get_type() const {
    return "Librarian";
}
