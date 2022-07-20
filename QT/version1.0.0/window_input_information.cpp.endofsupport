#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "window_input_information.h"
#include "ui_window_input_information.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "SqliteOperator.h"
#include <QString>

#include <QCoreApplication>
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

QString patient_name="UNKNOWN";
QString patient_gender="UNKNOWN";
QString patient_age="UNKNOWN";
QString patient_time="UNKNOWN";
QString patient_part="UNKNOWN";
QString patient_bad="UNKNOWN";

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
    patient_part=ui->textEdit_5->toPlainText();
}


void window_input_information::on_textEdit_4_textChanged()
{
    //输入病人的不良嗜好
    patient_bad=ui->textEdit_6->toPlainText();
}


void window_input_information::on_pushButton_clicked()
{
    //在此处连接数据库
    /*
    struct PATIENT_INFO
    {
        QString name=patient_name;               //患者姓名
        QString gender=patient_gender;           //患者性别
        QString age=patient_age;                 //患者年龄
        QString time=patient_time;               //就诊时间
        QString part=patient_part;               //患病部位
        QString bad=patient_bad;                 //不良嗜好
    };//patient_info;
    */
    patient_bad=ui->textEdit_6->toPlainText();
    patient_part=ui->textEdit_5->toPlainText();
    patient_time=ui->textEdit_4->toPlainText();
    patient_age=ui->textEdit_3->toPlainText();
    patient_gender=ui->textEdit_2->toPlainText();
    patient_name=ui->textEdit->toPlainText();
    PATIENT_INFO patient_info;
    patient_info.age=patient_age;
    patient_info.name=patient_name;
    patient_info.bad=patient_bad;
    patient_info.gender=patient_gender;
    patient_info.part=patient_part;
    patient_info.time=patient_time;
    qDebug()<<"name="<<patient_info.name<<"gender="<<patient_info.gender<<"age="<<patient_info.age<<"time="<<patient_info.time<<"part="<<patient_info.part<<"bad="<<patient_info.bad;
    //数据结构体创建完成
    //打开数据库
    SqliteOperator_patient_info query;
    query.openDb();
    query.createTable();
    //判断数据表是否存在
    QString str1=QString("PATIENT_INFO");
    if(query.isTableExisted_patient(str1))
    {
        qDebug()<<"isTabelExist:"<<"Exist";
    }
    else
    {
        qDebug()<<"isTabelExist:"<<"False";
        qDebug()<<"create a new table,please wait";
        query.createTable();
        qDebug()<<"table create finished";
    }
    //输入病人信息
    query.singleInsertData(patient_info);
    //关闭数据库
    query.closeDb();
    //弹窗提示
    QMessageBox::information(this,
                             tr("提示"),
                             tr("病人信息保存成功"),
                             QMessageBox::Ok);
    //关闭本窗口，退出本窗口
    this->close();
}

