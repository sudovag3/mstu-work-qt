#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

// Наследник класса User - Студент
class Student : public User {
public:
    // Конструктор, принимающий логин и пароль
    Student(const QString& login, const QString& password);
    Student(const QString& login, const QString& password, bool is_hashed);


    // Функция получения типа пользователя
    QString get_type() const override;
    static QList<Student> getStudents();
};

#endif // STUDENT_H
