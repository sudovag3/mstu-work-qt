#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QDialog>

namespace Ui {
class Studentform;
}

class Studentform : public QDialog
{
    Q_OBJECT

public:
    explicit Studentform(QWidget *parent = nullptr);
    ~Studentform();

private slots:
    void on_Vihod_clicked();

private:
    Ui::Studentform *ui;
};

#endif // STUDENTFORM_H
