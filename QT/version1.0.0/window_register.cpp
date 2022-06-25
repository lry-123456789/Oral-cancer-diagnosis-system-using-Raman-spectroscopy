
#include "window_register.h"
#include "ui_window_register.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

window_register::window_register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_register)
{
    ui->setupUi(this);
}

window_register::~window_register()
{
    delete ui;
}
