#include "bookform.h"
#include "ui_bookform.h"

BookForm::BookForm(const Book* book, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookForm),
    current_book(book) // инициализация текущей книги
{
    ui->setupUi(this);

    // Заполняем поля формы данными из книги
    ui->Name_Book->setText(book->title());
    ui->Author_Book->setText(book->author());
    ui->Opisanie_Book->setText(book->description());
    QPixmap bookCover(book->cover());
    ui->bookImage->setPixmap(bookCover.scaled(ui->bookImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // Если у вас есть поле для изображения в классе Book
    // ui->label_image->setPixmap(QPixmap::fromImage(book->image()));
}

BookForm::~BookForm()
{
    delete ui;
}
