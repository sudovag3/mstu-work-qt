#include "student.h"

// Конструктор класса Student
Student::Student(const QString& login, const QString& password)
    : User(login, password) {
    user_type_ = "student";
}

// Функция получения типа пользователя
QString Student::get_type() const {
    return "Student";
}
