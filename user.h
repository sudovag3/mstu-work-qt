#ifndef USER_H
#define USER_H

#include <QString>

// Базовый класс пользователя
class User {
public:
    // Конструктор, принимающий логин и пароль
    User(const QString& login, const QString& password, const QString& user_type);
    User(const QString &login, const QString &password_hash, const QString &type, bool is_hashed);


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

    static QString generate_salt();
    static QString hash_password(const QString& password, const QString& salt);

protected:
    QString login_;      // Логин пользователя
    QString password_;   // Пароль пользователя
    QString user_type_;  // Тип пользователя

    // Функция обновления данных в файле
    void update_file();
};


#endif // USER_H
