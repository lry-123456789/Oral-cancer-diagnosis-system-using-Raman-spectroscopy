#include "window_login.h"
#include "ui_window_login.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <SqliteOperator.h>

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

void window_login::on_lineEdit_textChanged(const QString &arg1)
{
    //ACCOUNT
}


void window_login::on_lineEdit_2_textChanged(const QString &arg1)
{
    //PASSWORD
}


void window_login::on_pushButton_clicked()
{
    //login_button
    /*************************************\
     * 此处获取用户输入的账号和密码
    \*************************************/
    QString ACCOUNT,PASSWORD;
    ACCOUNT=ui->lineEdit->text();
    PASSWORD=ui->lineEdit_2->text();
    /*************************************\
     * 在此处链接数据库文件
     * 如果数据库文件无法连接，则弹窗报错
    \*************************************/
    if(ACCOUNT==""||PASSWORD=="")
    {
        QMessageBox::critical(this,
                                tr("用户名或密码为空，请重新输入"),
                                tr("用户名或密码为空，请重新输入"),
                                QMessageBox::Ok);
    }
    else
    {
        /*************************************\
         * 在此处将用户输入的账号和密码与数据库中的账号密码进行对比
         * 如果对比成功，则进入主界面，否则弹窗报错
        \*************************************/
        SqliteOperator_user_account query;
        //打开数据库
        query.openDb();
        //开始对比数据库中时候存在用户名和密码
        if(query.isTableExisted_login(ACCOUNT,PASSWORD)==false)
        {
            //用户名或密码不存在
            QMessageBox::information(this,
                                     tr("错误"),
                                     tr("用户名或密码不存在，请重新输入"),
                                     QMessageBox::Ok);
            //query.closeDb();
        }
        else
        {
            //query.closeDb();
            //登录成功后关闭本界面
            MainWindow *w;
            w = new MainWindow();
            w->setWindowTitle("应用拉曼光谱的口腔癌诊断系统 v1.0.0");
            //this->close();            //本方法不适用，程序会加载主界面，1s后自动退出
            /*
             * 此处出现了同样的问题，说明可能不是上述close()或hide()方法引起的异常情况
            //this->hide();
            //w.show();
            */
            //此处考虑使用new语句新建一个窗口
            w->show();
            //隐藏本界面
            this->hide();
            //成功登录到本系统
        }
        query.closeDb();
        /******************\
        //登录成功后关闭本界面
        MainWindow *w;
        w = new MainWindow();
        w->setWindowTitle("应用拉曼光谱的口腔癌诊断系统 v1.0.0");
        //this->close();            //本方法不适用，程序会加载主界面，1s后自动退出
        ///*
        // * 此处出现了同样的问题，说明可能不是上述close()或hide()方法引起的异常情况
        //this->hide();
        //w.show();
        //*/
        //此处考虑使用new语句新建一个窗口
        /*********************8\
        w->show();
        //隐藏本界面
        this->hide();
        \********************************/
    }
}


void window_login::on_pushButton_2_clicked()
{
    //register_button

    /********************\
     * 此处连接注册界面
     * 注册界面名称为window_register
    \********************/

    //连接注册界面
    window_register *m;
    m=new window_register();
    m->setWindowTitle("新用户注册");
    m->show();
    //隐藏本界面
    this->hide();
}

