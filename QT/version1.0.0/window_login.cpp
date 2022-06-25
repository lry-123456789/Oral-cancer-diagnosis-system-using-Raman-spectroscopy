#include "window_login.h"
#include "ui_window_login.h"

window_login::window_login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_login)
{
    ui->setupUi(this);
}

window_login::~window_login()
{
    delete ui;
}
