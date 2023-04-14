#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "user.h"

// Наследник класса User - Библиотекарь
class Librarian : public User {
public:
    // Конструктор, принимающий логин и пароль
    Librarian(const QString& login, const QString& password);
    Librarian(const QString& login, const QString& password, bool is_hashed);

    // Функция получения типа пользователя
    QString get_type() const override;
};

#endif // LIBRARIAN_H
