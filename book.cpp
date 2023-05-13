#include "book.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include<QDebug>
#include <QCryptographicHash>
#include <QTime>


Book::Book(const QString& Idd_Book, const QString& Name_Book, const QString& Authors_Book, const QString& Opisanie_Book, const QString& Skin_Book, const QString& Kol_vo_Book)
    : Idd_Book_(Idd_Book), Name_Book_(Name_Book), Authors_Book_(Authors_Book), Opisanie_Book_(Opisanie_Book), Skin_Book_(Skin_Book), Kol_vo_Book_(Kol_vo_Book) {
    // Сохраняем инф о книге

    QFile file("books.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject books = doc.object();
    QJsonObject book;
    qInfo() << "Creating book " << Idd_Book_;
    book["Name_Book_"] = Name_Book;
    book["Authors_Book_"] = Authors_Book;
    book["Opisanie_Book_"] = Opisanie_Book;
    book["Skin_Book_"] = Skin_Book;
    book["Kol_vo_Book_"] = Kol_vo_Book;
    books[Idd_Book_] = book;
    doc.setObject(books);
    file.seek(0);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
    qInfo() << "Created book: " << Idd_Book_;
}
Book::~Book() {}

QString Book::get_Idd_Book() const {
    return Idd_Book_;
}
QString Book::get_Name_Book() const {
    return Name_Book_;
}
QString Book::get_Authors_Book() const {
    return Authors_Book_;
}
QString Book::get_Opisanie_Book() const {
    return Opisanie_Book_;
}
QString Book::get_Skin_Book() const {
    return Skin_Book_;
}
QString Book::get_Kol_vo_Book() const {
    return Kol_vo_Book_;
}



