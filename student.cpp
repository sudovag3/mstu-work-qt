#include "student.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

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

QList<Student> Student::getStudents() {
    QList<Student> students;
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return students;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = doc.object();

    foreach (const QString& key, users.keys()) {
        QJsonObject user = users[key].toObject();
        if (user["Type"].toString() == "student") {
            students.append(Student(key, user["password_hash"].toString(), true));
        }
    }
    return students;
}
