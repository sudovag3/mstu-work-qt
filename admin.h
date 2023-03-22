#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

// Наследник класса User - Админ
class Admin : public User {
public:
    // Конструктор, принимающий логин и пароль
    Admin(const QString& login, const QString& password);

    // Функция получения типа пользователя
    QString get_type() const override;
};

#endif // ADMIN_H
