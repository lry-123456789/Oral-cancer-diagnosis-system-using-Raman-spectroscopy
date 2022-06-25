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

private:
    Ui::window_input_information *ui;
};

#endif // WINDOW_INPUT_INFORMATION_H
