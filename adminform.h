#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QDialog>

namespace Ui {
class AdminForm;
}

class AdminForm : public QDialog
{
    Q_OBJECT

public:
    explicit AdminForm(QWidget *parent = 0);
    ~AdminForm();

signals:
    void userEdited();
    void userDeleted();

private slots:

    void update_user_list();

    void on_userEdited();

    void on_createUserButton_clicked();

    void on_ButtonClose_clicked();

private:
    Ui::AdminForm *ui;
};

#endif // ADMINFORM_H
