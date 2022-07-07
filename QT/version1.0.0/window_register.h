#ifndef WINDOW_REGISTER_H
#define WINDOW_REGISTER_H

#include <QMainWindow>

namespace Ui {
class window_register;
}

class window_register : public QMainWindow
{
    Q_OBJECT

public:
    explicit window_register(QWidget *parent = nullptr);
    ~window_register();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::window_register *ui;
};

#endif // WINDOW_REGISTER_H
