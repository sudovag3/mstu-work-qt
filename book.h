#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QList>
#include <QJsonObject>

class Book
{
public:
    Book(const QString& id, const QString& title, const QString& description, const QString& author, const QString& genre, const QString& cover, int quantity);
    Book(const QJsonObject &json);
    // Getters
    QString id() const;
    QString title() const;
    QString description() const;
    QString author() const;
    QString genre() const;
    QString cover() const;
    int quantity() const;
    QJsonObject toJson() const;

    // Setters
    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setAuthor(const QString &author);
    void setGenre(const QString &genre);
    void setQuantity(int quantity);
    void setCover(const QString &cover);


    // CRUD operations
    static QList<Book> books(const QString& filterAuthor, const QString& filterTitle);
    static Book getBookById(const QString& id);
    void save();
    void remove();


    bool operator==(const Book &other) const;

private:
    QString id_;
    QString title_;
    QString description_;
    QString author_;
    QString genre_;
    QString cover_;
    int quantity_;
};

#endif // BOOK_H
