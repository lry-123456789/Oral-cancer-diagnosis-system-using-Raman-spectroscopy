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

private:
    Ui::window_register *ui;
};

#endif // WINDOW_REGISTER_H
