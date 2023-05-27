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

    QString login;
    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;


private slots:
    void on_Vihod_clicked();

    void update_student();

    // Слот добавления нового текста в массив текстов
    void on_AddButton_clicked();

private:
    Ui::Studentform *ui;
};

#endif // STUDENTFORM_H
