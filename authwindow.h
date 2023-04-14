#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = 0);
    ~AuthWindow();
private slots:
    void on_loginButton_clicked();

private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
