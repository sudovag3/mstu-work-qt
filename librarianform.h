#ifndef LIBRARIANFORM_H
#define LIBRARIANFORM_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class Librarianform;
}

class Librarianform : public QDialog
{
    Q_OBJECT

public:
    explicit Librarianform(QWidget *parent = nullptr);
    void update_book_list(const QString& author = QString(), const QString& title = QString());
    ~Librarianform();

private slots:
    void on_ButtonClose_clicked();

    void on_Downloadimage_clicked();

    void on_createBookButton_clicked();

    void on_bookEdited();

    void on_searchButton_clicked();

signals:
    void bookDeleted();


private:
    Ui::Librarianform *ui;
};

#endif // LIBRARIANFORM_H
