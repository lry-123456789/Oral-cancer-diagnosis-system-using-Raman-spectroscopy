#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "window_input_information.h"
#include "ui_window_input_information.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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

QString patient_name="";
QString patient_gender="";
QString patient_age="";
QString patient_time="";
QString patient_part="";
QString patient_bad="";

void window_input_information::on_textEdit_textChanged()
{
    //输入病人姓名
    patient_name=ui->textEdit->toPlainText();
}


void window_input_information::on_textEdit_5_textChanged()
{
    //输入病人性别
    patient_gender=ui->textEdit_2->toPlainText();
}


void window_input_information::on_textEdit_2_textChanged()
{
    //输入病人年龄
    patient_age=ui->textEdit_3->toPlainText();
}


void window_input_information::on_textEdit_6_textChanged()
{
    //输入病人就诊时间
    patient_time=ui->textEdit_4->toPlainText();
}


void window_input_information::on_textEdit_3_textChanged()
{
    //输入病人患病部位
    patient_time=ui->textEdit_5->toPlainText();
}


void window_input_information::on_textEdit_4_textChanged()
{
    //输入病人的不良嗜好
    patient_time=ui->textEdit_6->toPlainText();
}


void window_input_information::on_pushButton_clicked()
{
    //在此处连接数据库

    //弹窗提示
    QMessageBox::information(this,
                             tr("提示"),
                             tr("病人信息保存成功"),
                             QMessageBox::Ok);
    //关闭本窗口，退出本窗口
    this->close();
}

