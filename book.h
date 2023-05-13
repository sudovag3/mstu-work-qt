#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book {
public:
    // Конструктор, информацию книги
    Book(const QString& Idd_Book, const QString& Name_Book, const QString& Authors_Book, const QString& Opisanie_Book, const QString& Skin_Book, const QString& Kol_vo_Book);

    // Виртуальный деструктор
    virtual ~Book();

    QString get_Idd_Book() const;
    QString get_Name_Book() const;
    QString get_Authors_Book() const;
    QString get_Opisanie_Book() const;
    QString get_Skin_Book() const;
    QString get_Kol_vo_Book() const;

protected:
    QString Idd_Book_;        // Id книги
    QString Name_Book_;      // название книги
    QString Authors_Book_;   // автор книги
    QString Opisanie_Book_;  // описание книги
    QString Skin_Book_;      // обложка книги
    QString Kol_vo_Book_;    // количество экземпляров книги
};

#endif // BOOK_H
