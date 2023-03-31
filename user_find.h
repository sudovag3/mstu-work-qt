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
        QString password = user["password"].toString();
        QString user_type = user["Type"].toString();

        if (user_type == "admin") {
            users_list.append(new Admin(login, password));
        } else if (user_type == "student") {
            users_list.append(new Student(login, password));
        } else if (user_type == "librarian") {
            users_list.append(new Librarian(login, password));
        } else {
            users_list.append(new User(login, password, user_type));
        }
    }

    return users_list;
}
#endif // USER_FIND_H
