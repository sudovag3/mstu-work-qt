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
    ~Librarianform();

private slots:

    void on_ButtonClose_clicked();

    void on_Downloadimage_clicked();

private:
    Ui::Librarianform *ui;
};

#endif // LIBRARIANFORM_H
