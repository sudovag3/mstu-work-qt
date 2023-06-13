#include "book.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Book::Book(const QString& id, const QString& title, const QString& description, const QString& author, const QString& genre, const QString& cover, int quantity, const QString& link)
    : id_(id), title_(title), description_(description), author_(author), genre_(genre), cover_(cover), quantity_(quantity), link_(link) {
    save();
}

Book::Book(const QJsonObject &json) {
    id_ = json["id"].toString();
    title_ = json["title"].toString();
    cover_ = json["cover"].toString();
    link_ = json["link"].toString();
    description_ = json["description"].toString();
    author_ = json["author"].toString();
    genre_ = json["genre"].toString();
    quantity_ = json["quantity"].toInt();
}

QString Book::link() const {
    return link_;
}

QString Book::id() const {
    return id_;
}

QString Book::title() const {
    return title_;
}

QString Book::description() const {
    return description_;
}

QString Book::author() const {
    return author_;
}

QString Book::genre() const {
    return genre_;
}

int Book::quantity() const {
    return quantity_;
}

QString Book::cover() const {
    return cover_;
}

void Book::setLink(const QString &link) {
    if (link != link_) {
        link_ = link;
        save();
    }
}

void Book::setTitle(const QString &title) {
    if (title != title_) {
        title_ = title;
        save();
    }
}

void Book::setDescription(const QString &description) {
    if (description != description_) {
        description_ = description;
        save();
    }
}

void Book::setAuthor(const QString &author) {
    if (author != author_) {
        author_ = author;
        save();
    }
}

void Book::setGenre(const QString &genre) {
    if (genre != genre_) {
        genre_ = genre;
        save();
    }
}

void Book::setQuantity(int quantity) {
    if (quantity != quantity_) {
        quantity_ = quantity;
        save();
    }
}

void Book::setCover(const QString &cover) {
    if (cover != cover_) {
        cover_ = cover;
        save();
    }
}

bool Book::operator==(const Book &other) const {
    return id_ == other.id();
}

// Method to get all books
QList<Book> Book::books(const QString& filterAuthor, const QString& filterTitle) {
    QList<Book> booksList;
    QFile file("books.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return booksList;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject books = doc.object();
    file.close();

    for (auto key : books.keys()) {
        QJsonObject jsonBook = books[key].toObject();
        Book book(jsonBook);

        if (!filterAuthor.isEmpty() && book.author() != filterAuthor)
            continue;
        if (!filterTitle.isEmpty() && book.title() != filterTitle)
            continue;

        booksList.append(book);
    }

    return booksList;
}

// Method to get a book by id
Book Book::getBookById(const QString & id) {
    QFile file("books.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file";
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject books = doc.object();
    file.close();

    if (!books.contains(id)) {
        qWarning() << "Unknown book";
    }

    QJsonObject jsonBook = books[id].toObject();
    return {jsonBook};
}

// Method to save a book
void Book::save() {
    QFile file("books.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject books = doc.object();

    books[id_] = toJson();

    doc.setObject(books);
    file.seek(0);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
}

// Method to remove a book
void Book::remove() {
    QFile file("books.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject books = doc.object();

    if (!books.contains(id_)) {
        qWarning() << "Unknown book";
        return;
    }

    books.remove(id_);

    doc.setObject(books);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write(doc.toJson());
    if (!file.flush()) {
        qWarning() << "Failed to write data to file";
    }
    file.close();
}




// Conversion to JSON
QJsonObject Book::toJson() const {
    QJsonObject json;
    json["id"] = id_;
    json["title"] = title_;
    json["description"] = description_;
    json["author"] = author_;
    json["genre"] = genre_;
    json["quantity"] = quantity_;
    json["cover"] = cover_;
    json["link"] = link_;
    return json;
}
