#include "studentbook.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QString>
#include<QDebug>
#include <QCryptographicHash>
#include <QTime>

StudentBook::StudentBook(const QString& login, const QString& Idd_Book)
    : login_(login), Idd_Book_(Idd_Book){
    // Сохраняем логин и пароль в файл

    QFile file("studentbooks.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject studentbooks = doc.object();
    QJsonObject studentbook;
    qInfo() << "Creating studentbooks " << login_;
    studentbook["Idd_Book"] = Idd_Book_;

    QJsonArray textsArray = studentbooks[login_].toArray();
    textsArray.append(studentbook);

    studentbooks[login_]=textsArray;

    doc.setObject(studentbooks);
    file.seek(0);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
    qInfo() << "Created studentbooks: " << login_;
}
// Виртуальный деструктор класса User
StudentBook::~StudentBook() {}
