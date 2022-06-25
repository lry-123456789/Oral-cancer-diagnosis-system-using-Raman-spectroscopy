#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <window_input_information.h>
#include <ui_window_input_information.h>
#include <window_login.h>
#include <ui_window_login.h>
#include <window_register.h>
#include <ui_window_register.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    window_input_information *input_info;
    window_login *login_sys;
    window_register *register_sys;
};
#endif // MAINWINDOW_H
