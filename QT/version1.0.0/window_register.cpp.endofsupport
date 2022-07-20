
#include "window_register.h"
#include "ui_window_register.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <SqliteOperator.h>


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

void window_register::on_lineEdit_textChanged(const QString &arg1)
{
    //NEW_ACCOUNT
}


void window_register::on_lineEdit_2_textChanged(const QString &arg1)
{
    //NEW_PASSWORD
}


void window_register::on_lineEdit_3_textChanged(const QString &arg1)
{
    //NEW_PASSWORD_CHECK
}


void window_register::on_pushButton_clicked()
{
    //注册
    QString NEW_ACCOUNT ,NEW_PASSWORD ,NEW_PASSWORD_CHECK;
    NEW_ACCOUNT=ui->lineEdit->text();
    NEW_PASSWORD=ui->lineEdit_2->text();
    NEW_PASSWORD_CHECK=ui->lineEdit_3->text();
    if(NEW_ACCOUNT==NEW_PASSWORD)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("用户名不能与密码相同"),
                                 QMessageBox::Ok);
    }
    /*
    else if(NEW_PASSWORD.length()<8)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("密码长度过短，密码长度必须大于或等于8位数"),
                                 QMessageBox::Ok);
    }
    else if(NEW_PASSWORD.length()>255)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("密码长度过长，密码长度必须小于256"),
                                 QMessageBox::Ok);
    }
    else if(NEW_PASSWORD!=NEW_PASSWORD_CHECK)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("两次密码不一致，请重新输入"),
                                 QMessageBox::Ok);
    }
    */
    else
    {
        //在此处连接数据库，检测用户名是否被使用过
        SqliteOperator_user_account query;
        query.openDb();
        query.createTable();
        //query=QSqlQuery::QSqlQuery(database);
        if(query.isTableExisted_register(NEW_ACCOUNT)==true)
        {
            QMessageBox::critical(this,
                                  tr("错误"),
                                  tr("用户名已经被使用"),
                                  QMessageBox::Ok);
            query.closeDb();
        }
        else
        {

            //在此处连接数据库，将账号和密码保存(未被使用)
            USER_ACCOUNT data;
            data.ACCOUNT=NEW_ACCOUNT;
            data.PASSWORD=NEW_PASSWORD;
            query.insertData(data);
            //提示注册成功
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("创建用户成功，请登陆"),
                                     QMessageBox::Ok);
            query.closeDb();
            //此处返回登录界面
            window_login *log_i;
            log_i =new window_login();
            log_i->setWindowTitle("登录到应用拉曼光谱的口腔癌诊断系统");
            log_i->show();
            this->hide();
        }
    }
}

