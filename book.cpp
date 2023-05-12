#include "book.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include<QDebug>
#include <QCryptographicHash>
#include <QTime>
/*
Book::Book(const QString& Name_Book, const QString& Authors_Book, const QString& Nalichie)
    : Name_Book_(Name_Book), Authors_Book_(Authors_Book), Nalichie_(Nalichie) {
    // Сохраняем название и автора книги в файл

    QString salt = generate_salt();
    QString password_hash = hash_password(password, salt);

    QFile file("books.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject books = doc.object();
    QJsonObject book;
    qInfo() << "Creating book " << Name_Book_;
    user["Authors_Book_"] = Authors_Book;
    user["Nalichie"] = Nalichie_;
    users[Name_Book_] = book;
    doc.setObject(books);
    file.seek(0);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
    qInfo() << "Created book: " << Name_Book_;
}
*/
