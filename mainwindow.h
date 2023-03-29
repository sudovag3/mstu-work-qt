#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authwindow.h"
#include "adminform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showAdminForm();
    ~MainWindow();

private slots:
    void on_authFormButton_clicked();


private:
    Ui::MainWindow *ui;
    AuthWindow * authWindow;
    AdminForm * adminWindow;

};

#endif // MAINWINDOW_H
