#ifndef STUDENTBOOK_H
#define STUDENTBOOK_H

#include <QString>
#include<QJsonObject>

class StudentBook
{
public:
    StudentBook(const QString& login, const QString& Idd_Book);

    // Виртуальный деструктор
    virtual ~StudentBook();


protected:
    QString login_;      // Логин пользователя
    QString Idd_Book_;
};

#endif // STUDENTBOOK_H
