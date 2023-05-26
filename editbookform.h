#ifndef EDITBOOKFORM_H
#define EDITBOOKFORM_H

#include <QDialog>
#include "book.h"

namespace Ui {
class EditBookForm;
}

class EditBookForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookForm(const Book *book, QWidget *parent = nullptr);
    ~EditBookForm();

signals:
    void bookEdited();

private slots:
    void on_saveBookButton_clicked();
    void on_Downloadimage_clicked();

private:
    Ui::EditBookForm *ui;
    const Book *book_;
};

#endif // EDITBOOKFORM_H
