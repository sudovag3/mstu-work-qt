#include "studentform.h"
#include "user.h"
#include "ui_studentform.h"
#include "authwindow.h"
#include "studentbook.h"
#include "book.h"
#include "bookform.h"

#include <QString>
#include <QUrl>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QDesktopServices>
#include <QList>
#include <QPushButton>
#include <QString>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QPointer>
#include <QGridLayout>


Studentform::Studentform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Studentform)
{
    ui->setupUi(this);
    update_bibl_book_list("", "");
//    update_student_book_list();
}

Studentform::~Studentform()
{
    delete ui;
}

void Studentform::update_student_book_list() {
    ui->BookListWidget->clear();
    QList<Book> student_books = StudentBook::getBooksByStudent(login);
    for (Book &book : student_books) {
        QString book_info = QString("Название: %1, Автор: %2, Описание: %3")
                            .arg(book.title())
                            .arg(book.author())
                            .arg(book.description());

        QListWidgetItem* item = new QListWidgetItem();
        ui->BookListWidget->addItem(item);
        item->setSizeHint(QSize(0, 50)); // Adjust the size to fit your widget

        QWidget* widget = new QWidget();
        QLabel* label = new QLabel(book_info);
        QPushButton* viewButton = new QPushButton("Смотреть");
        QPushButton* returnButton = new QPushButton("Вернуть");

        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(label);
        layout->addWidget(viewButton);
        layout->addWidget(returnButton);
        widget->setLayout(layout);

        ui->BookListWidget->setItemWidget(item, widget);

        connect(viewButton, &QPushButton::clicked, [=]() {
            QDesktopServices::openUrl(QUrl::fromUserInput(book.link()));
        });

        connect(returnButton, &QPushButton::clicked, [=]() {
            StudentBook::returnBook(login, book);
            update_student_book_list();
            update_bibl_book_list("", "");
        });
    }
}

void Studentform::update_bibl_book_list(const QString& author, const QString& title) {
    ui->BiblListWidget->clear();

    QList<Book> all_books = Book::books(author, title);
    QList<Book> student_books = StudentBook::getBooksByStudent(login);

    for (Book &book : all_books) {
        if (student_books.contains(book)) {
            continue;
        } // Skip if the student already has the book

        QString book_info = QString("Название: %1, Автор: %2, Описание: %3")
                            .arg(book.title())
                            .arg(book.author())
                            .arg(book.description());

        QListWidgetItem* item = new QListWidgetItem();
        ui->BiblListWidget->addItem(item);
        item->setSizeHint(QSize(0, 50)); // Adjust the size to fit your widget

        QWidget* widget = new QWidget();
        QLabel* label = new QLabel(book_info);
//        QPushButton* detailButton = new QPushButton("Подробнее");
        QPushButton* takeButton = new QPushButton("Взять");

        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(label);
//        layout->addWidget(detailButton);
        layout->addWidget(takeButton);
        widget->setLayout(layout);

        ui->BiblListWidget->setItemWidget(item, widget);

//        connect(detailButton, &QPushButton::clicked, [=]() {
//            BookForm *bookForm = new BookForm(&book);
//            bookForm->setModal(true);
//            bookForm->open();
//        });

        connect(takeButton, &QPushButton::clicked, [=]() {
            StudentBook::takeBook(login, book);
            update_student_book_list();
            update_bibl_book_list("", "");
        });
    }
}


void Studentform::on_Vihod_clicked()
{
    AuthWindow *authwind = new AuthWindow(this);
    authwind->show();
    this->hide();
}

void Studentform::on_searchButton_clicked() {

    QString author = ui->searchAutorEdit->text();
    QString title = ui->searchTitleEdit->text();
    qInfo() << author << title;

    update_bibl_book_list(author, title);
}
