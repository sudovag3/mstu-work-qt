#include "librarian.h"

// Конструктор класса Librarian
Librarian::Librarian(const QString& login, const QString& password)
    : User(login, password, "librarian") {
}

Librarian::Librarian(const QString& login, const QString& password, bool is_hashed)
    : User(login, password, "librarian", is_hashed) {
}

// Функция получения типа пользователя
QString Librarian::get_type() const {
    return "Librarian";
}
