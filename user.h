#ifndef USER_H
#define USER_H

#include <QString>

// Базовый класс пользователя
class User {
public:
    // Конструктор, принимающий логин и пароль
    User(const QString& login, const QString& password, const QString& user_type);

    // Виртуальный деструктор
    virtual ~User();

    // Функция поиска пользователя по логину и паролю
    static User* find_user(const QString& login, const QString& password);

    // Функции изменения логина и пароля
    virtual void set_login(const QString& login);
    virtual void set_password(const QString& password);

    // Функции получения логина, пароля и типа пользователя
    QString get_login() const;
    QString get_password() const;
    virtual QString get_type() const;

protected:
    QString login_;      // Логин пользователя
    QString password_;   // Пароль пользователя
    QString user_type_;  // Тип пользователя

    // Функция обновления данных в файле
    void update_file();
};


#endif // USER_H
