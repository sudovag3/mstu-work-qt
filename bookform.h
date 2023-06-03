#ifndef BOOKFORM_H
#define BOOKFORM_H

#include <QDialog>
#include "book.h"

namespace Ui {
class BookForm;
}

class BookForm : public QDialog
{
    Q_OBJECT

public:
    explicit BookForm(const Book* book, QWidget *parent = nullptr); // модифицированный конструктор
    ~BookForm();

private:
    Ui::BookForm *ui;
    const Book* current_book; // текущая книга
};

#endif // BOOKFORM_H
