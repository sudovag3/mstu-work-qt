#include "student.h"

// Конструктор класса Student
Student::Student(const QString& login, const QString& password)
    : User(login, password, "student") {
}

Student::Student(const QString& login, const QString& password, bool is_hashed)
    : User(login, password, "student", is_hashed) {
}

// Функция получения типа пользователя
QString Student::get_type() const {
    return "Student";
}
