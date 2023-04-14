#include "user.h"
#include "admin.h"
#include "librarian.h"
#include "student.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include<QDebug>
#include <QCryptographicHash>
#include <QTime>


// Конструктор класса User
User::User(const QString& login, const QString& password, const QString& user_type)
    : login_(login), password_(password), user_type_(user_type) {
    // Сохраняем логин и пароль в файл

    QString salt = generate_salt();
    QString password_hash = hash_password(password, salt);

    QFile file("users.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject users = doc.object();
    QJsonObject user;
    qInfo() << "Creating user " << login_;
    user["password_hash"] = password_hash;
    user["salt"] = salt;
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

User::User(const QString &login, const QString &password_hash, const QString &user_type, bool is_hashed)
    : login_(login), password_(password_hash), user_type_(user_type) {

    QFile file("users.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = doc.object();
    if (!users.contains(login)) {
        qWarning() << "Uknown user";
        return;
    }

    QJsonObject user = users[login].toObject();
    if (user["password_hash"].toString() != password_hash) {
        qWarning() << "Incorrect password";
        return;
    }

}

// Виртуальный деструктор класса User
User::~User() {}

// Функция для хэширования пароля с солью
// Аргументы:
// - password: сырой пароль, который нужно хэшировать
// - salt: соль, которая будет добавлена к паролю перед хэшированием
QString User::hash_password(const QString& password, const QString& salt) {
    // Создаем объект QCryptographicHash, который будет выполнять хэширование
    // с использованием алгоритма SHA-256
    QCryptographicHash hash(QCryptographicHash::Sha256);

    // Добавляем пароль и соль вместе в хэш-функцию
    // toUtf8() преобразует QString в QByteArray, так как addData ожидает QByteArray
    hash.addData((password + salt).toUtf8());

    // Получаем хэш в виде QByteArray и преобразуем его в шестнадцатеричную строку
    return hash.result().toHex();
}

// Функция для генерации случайной соли
QString User::generate_salt() {
    // Инициализируем генератор случайных чисел с помощью текущего времени
    // Время используется для получения "семени" (seed) для генератора случайных чисел,
    // чтобы каждый раз при запуске программы генерировались разные случайные числа
    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec() + time.second() * 1000));

    QString salt; // Строка для хранения соли

    // Цикл генерации 16 символов для соли
    for (int i = 0; i < 16; ++i) {
        int rand_value = qrand() % 62; // Генерируем случайное число от 0 до 61

        // Конвертируем случайное число в символ и добавляем его к соли:
        if (rand_value < 10) { // Если число от 0 до 9, добавляем соответствующую цифру
            salt.append(rand_value + '0');
        } else if (rand_value < 36) { // Если число от 10 до 35, добавляем соответствующую заглавную букву
            salt.append(rand_value - 10 + 'A');
        } else { // Если число от 36 до 61, добавляем соответствующую строчную букву
            salt.append(rand_value - 36 + 'a');
        }
    }
    return salt; // Возвращаем сгенерированную соль
}


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
    QString salt = user["salt"].toString();
    QString password_hash = hash_password(password, salt);
    if (user["password_hash"].toString() != password_hash) {
        return nullptr;
    }
    // Найден пользователь, создаем соответствующий объект
    QString user_type = user["Type"].toString();
    if (user_type == "admin") {
        return new Admin(login, password_hash, true);
    } else if (user_type == "student") {
        return new Student(login, password_hash, true);
    } else if (user_type == "librarian") {
        return new Librarian(login, password_hash, true);
    } else {
        return new User(login, password_hash, user_type, true);
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
    QString new_salt = generate_salt();
    QString new_password_hash = hash_password(password, new_salt);
    user["password_hash"] = new_password_hash;
    user["salt"] = new_salt;
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
