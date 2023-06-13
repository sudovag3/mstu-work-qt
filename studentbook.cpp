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

QList<Book> StudentBook::getBooksByStudent(const QString& student_login) {
    QList<Book> result;
    QFile file("studentbooks.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return result;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject student_books = doc.object();
    QJsonArray books = student_books[student_login].toArray();
    for (const QJsonValue &value : books) {
        QJsonObject obj = value.toObject();
        QString idd_book = obj["Idd_Book"].toString();
        Book book = Book::getBookById(idd_book);  // предполагается, что у вас есть метод getBookById в классе Book
        result.append(book);
    }

    file.close();
    return result;
}

void StudentBook::returnBook(const QString& student_login, const Book& book) {
    QFile file("studentbooks.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject student_books = doc.object();
    QJsonArray books = student_books[student_login].toArray();

    // Создаем новый массив JSON
    QJsonArray newBooks;
    for (QJsonArray::iterator it = books.begin(); it != books.end(); it++) {
        QJsonObject obj = it->toObject();
        QString idd_book = obj["Idd_Book"].toString();
        // Только те книги, которые не соответствуют удаляемой книге, добавляются в новый список
        if (book.id() != idd_book) {
            newBooks.push_back(obj);
        }
    }

    student_books[student_login] = newBooks;
    doc.setObject(student_books);
    file.seek(0);
    file.write(doc.toJson());
    file.resize(file.pos());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
}

bool StudentBook::checkBook(const QString& student_login, const Book& book) {
    QFile file("studentbooks.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject student_books = doc.object();
    QJsonArray books = student_books[student_login].toArray();

    for (QJsonArray::iterator it = books.begin(); it != books.end(); it++) {
        QJsonObject obj = it->toObject();
        QString idd_book = obj["Idd_Book"].toString();
        // Если ID книги совпадает с ID любой из книг студента, возвращаем true
        if (book.id() == idd_book) {
            file.close();
            return true;
        }
    }

    // Если ни одно из ID книг не совпало, возвращаем false
    file.close();
    return false;
}



void StudentBook::takeBook(const QString& student_login, const Book& book) {
    QFile file("studentbooks.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject student_books = doc.object();
    QJsonObject studentbook;
    studentbook["Idd_Book"] = book.id();

    QJsonArray books = student_books[student_login].toArray();
    books.append(studentbook);

    student_books[student_login] = books;

    doc.setObject(student_books);
    file.seek(0);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
}


// Виртуальный деструктор класса User
StudentBook::~StudentBook() {}
