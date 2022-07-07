#ifndef WINDOW_INPUT_INFORMATION_H
#define WINDOW_INPUT_INFORMATION_H

#include <QMainWindow>

namespace Ui {
class window_input_information;
}

class window_input_information : public QMainWindow
{
    Q_OBJECT

public:
    explicit window_input_information(QWidget *parent = nullptr);
    ~window_input_information();

private slots:
    void on_textEdit_textChanged();

    void on_textEdit_5_textChanged();

    void on_textEdit_2_textChanged();

    void on_textEdit_6_textChanged();

    void on_textEdit_3_textChanged();

    void on_textEdit_4_textChanged();

    void on_pushButton_clicked();

private:
    Ui::window_input_information *ui;
};

#endif // WINDOW_INPUT_INFORMATION_H
