#include "window_input_information.h"
#include "ui_window_input_information.h"

window_input_information::window_input_information(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_input_information)
{
    ui->setupUi(this);
}

window_input_information::~window_input_information()
{
    delete ui;
}
