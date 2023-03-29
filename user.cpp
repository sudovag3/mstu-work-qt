#include "user.h"
#include "admin.h"
#include "librarian.h"
#include "student.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include<QDebug>

// Конструктор класса User
User::User(const QString& login, const QString& password, const QString& user_type)
    : login_(login), password_(password), user_type_(user_type) {
    // Сохраняем логин и пароль в файл
    QFile file("users.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject users = doc.object();
    QJsonObject user;
    qInfo() << "Creating user " << login_;
    user["password"] = password_;
    user["Type"] = user_type_;
    users[login_] = user;
    doc.setObject(users);
    file.seek(0);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
    qInfo() << "Created user: " << login_;
}

// Виртуальный деструктор класса User
User::~User() {}

// Функция поиска пользователя по логину и паролю
User* User::find_user(const QString& login, const QString& password) {
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = doc.object();
    if (!users.contains(login)) {
        return nullptr;
    }
    QJsonObject user = users[login].toObject();
    if (user["password"].toString() != password) {
        return nullptr;
    }
    // Найден пользователь, создаем соответствующий объект
    QString user_type = user["Type"].toString();
    if (user_type == "admin") {
        return new Admin(login, password);
    } else if (user_type == "student") {
        return new Student(login, password);
    } else if (user_type == "librarian") {
        return new Librarian(login, password);
    } else {
        return new User(login, password, user_type);
    }
}

// Функция изменения логина
void User::set_login(const QString& login) {
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = doc.object();
    if (!users.contains(login_)) {
        return;
    }
    QJsonObject user = users.take(login_).toObject();
    users[login] = user;
    doc.setObject(users);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write(doc.toJson());
    file.close();
    login_ = login;
}

// Функция изменения пароля
void User::set_password(const QString& password) {
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = doc.object();
    if (!users.contains(login_)) {
        return;
    }
    QJsonObject user = users[login_].toObject();
    user["password"] = password;
    users[login_] = user;
    doc.setObject(users);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write(doc.toJson());
    file.close();
    password_ = password;
}

// Функция получения логина
QString User::get_login() const {
    return login_;
}

// Функция получения пароля
QString User::get_password() const {
    return password_;
}

// Функция получения типа пользователя
QString User::get_type() const {
    return user_type_;
}

// Функция обновления данных в файле
void User::update_file() {
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = doc.object();
    if (!users.contains(login_)) {
        return;
    }
    QJsonObject user = users[login_].toObject();
    user["password"] = password_;
    users[login_] = user;
    doc.setObject(users);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write(doc.toJson());
    file.close();
}
