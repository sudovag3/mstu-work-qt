#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QDialog>

#include <QString>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

namespace Ui {
class Studentform;
}

class Studentform : public QDialog
{
    Q_OBJECT

public:
    explicit Studentform(QWidget *parent = 0);
    ~Studentform();

    void update_student_book_list();
    void update_bibl_book_list(const QString& author, const QString& title);

    QString login;
    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;


private slots:
    void on_Vihod_clicked();


    void on_searchButton_clicked();

private:
    Ui::Studentform *ui;
};

#endif // STUDENTFORM_H
