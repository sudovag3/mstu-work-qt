#include "editbookform.h"
#include "ui_editbookform.h"
#include <QFileDialog>
#include <QMessageBox>

EditBookForm::EditBookForm(const Book *book, QWidget *parent)
    : QDialog(parent), book_(book), ui(new Ui::EditBookForm) {
    ui->setupUi(this);
    connect(ui->saveBookButton, &QPushButton::clicked, this, &EditBookForm::on_saveBookButton_clicked);
    connect(ui->Downloadimage, &QPushButton::clicked, this, &EditBookForm::on_Downloadimage_clicked);
    // Заполняем поля формы текущими значениями книги
    ui->titleEdit->setText(book_->title());
    ui->autorEdit->setText(book_->author());
    ui->DescriptionEdit->setText(book_->description());
    ui->genreEdit->setText(book_->genre());
    ui->linkEdit->setText(book_->link());
    ui->quantityBox->setValue(book_->quantity());
    ui->imagePathEdit->setText(book_->cover());
}

EditBookForm::~EditBookForm() {
    delete ui;
}

void EditBookForm::on_saveBookButton_clicked() {
    // Сохраняем измененные данные книги
    Book::getBookById(book_->id()).setTitle(ui->titleEdit->text());
    Book::getBookById(book_->id()).setAuthor(ui->autorEdit->text());
    Book::getBookById(book_->id()).setDescription(ui->DescriptionEdit->toPlainText());
    Book::getBookById(book_->id()).setGenre(ui->genreEdit->text());
    Book::getBookById(book_->id()).setQuantity(ui->quantityBox->value());
    Book::getBookById(book_->id()).setCover(ui->imagePathEdit->text());
    Book::getBookById(book_->id()).setLink(ui->linkEdit->text());
    // Вызываем сигнал, что книга была изменена
    emit bookEdited();
}

void EditBookForm::on_Downloadimage_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename, QString()) !=0){
        QImage image;
        bool valid = image.load(filename);

        if(valid){
          image = image.scaledToWidth( ui->Lbl_image->width(), Qt::SmoothTransformation);
          image = image.scaledToHeight( ui->Lbl_image->height(), Qt::SmoothTransformation);
          ui->Lbl_image->setPixmap(QPixmap::fromImage(image));
          ui->imagePathEdit->setText(filename);
        }
        else {
            QMessageBox::information(this, tr("Ошибка"),
                                     tr("Обложка не загруженна!"));
        }
    }
}
