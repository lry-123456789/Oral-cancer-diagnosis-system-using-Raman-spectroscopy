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

private slots:
    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_textBrowser_anchorClicked(const QUrl &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_progressBar_valueChanged(int value);

    void on_progressBar_2_valueChanged(int value);

    void on_progressBar_3_valueChanged(int value);

    void on_progressBar_4_valueChanged(int value);

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_12_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_16_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_18_clicked();

    void on_radioButton_17_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_radioButton_19_clicked();

    void on_radioButton_20_clicked();

    void on_action_save_data_normal_triggered();

private:
    Ui::MainWindow *ui;
    window_input_information *input_info;
    window_login *login_sys;
    window_register *register_sys;
};
#endif // MAINWINDOW_H
