#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

// Наследник класса User - Студент
class Student : public User {
public:
    // Конструктор, принимающий логин и пароль
    Student(const QString& login, const QString& password);

    // Функция получения типа пользователя
    QString get_type() const override;
};

#endif // STUDENT_H
