#ifndef USER_FIND_H
#define USER_FIND_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "user.h"
#include "admin.h"
#include "librarian.h"
#include "student.h"

QList<User*> read_users_from_file() {
    QList<User*> users_list;

    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return users_list;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject users = doc.object();
    for (QString key : users.keys()) {
        QJsonObject user = users[key].toObject();
        QString login = key;
        QString password_hash = user["password_hash"].toString();
        QString user_type = user["Type"].toString();

        if (user_type == "admin") {
            users_list.append(new Admin(login, password_hash, true));
        } else if (user_type == "student") {
            users_list.append(new Student(login, password_hash, true));
        } else if (user_type == "librarian") {
            users_list.append(new Librarian(login, password_hash, true));
        } else {
            users_list.append(new User(login, password_hash, user_type, true));
        }
    }

    return users_list;
}
#endif // USER_FIND_H
