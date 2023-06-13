#ifndef STUDENTBOOK_H
#define STUDENTBOOK_H

#include <QString>
#include<QJsonObject>
#include "book.h"

class StudentBook
{
public:
    StudentBook(const QString& login, const QString& Idd_Book);
    static QList<Book> getBooksByStudent(const QString& student_login);
    static void returnBook(const QString& student_login, const Book& book);
    static void takeBook(const QString& student_login, const Book& book);
    static bool checkBook(const QString& student_login, const Book& book);
    // Виртуальный деструктор
    virtual ~StudentBook();


protected:
    QString login_;      // Логин пользователя
    QString Idd_Book_;
};

#endif // STUDENTBOOK_H
