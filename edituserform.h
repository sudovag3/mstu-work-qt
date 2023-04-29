#ifndef EDITUSERFORM_H
#define EDITUSERFORM_H

#include <QDialog>
#include "user.h"


namespace Ui {
class EditUserForm;
}

class EditUserForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserForm(User *user, QWidget *parent = 0);
    ~EditUserForm();

signals:
    void userEdited();

private slots:
    void on_editUserButton_clicked();

private:
    Ui::EditUserForm *ui;
    User *user_;
};

#endif // EDITUSERFORM_H
