#include "SqliteOperator.h"
#include <stdio.h>
#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets/QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

#include <QMessageBox>

/**********************************\
 * 该部分为用户的注册操作所使用的链接数据库，操作数据库指令
 * 版本1.0.0
 * 编辑时间2022.7.3
\**********************************/
SqliteOperator_user_account::SqliteOperator_user_account()
{
    FILE *f1=fopen("account.db","rb");
    if(f1==NULL)
    {
        //数据库不存在
        //创建数据库
        QSqlDatabase database =QSqlDatabase::addDatabase("ACCOUNT_AND_PASSWORD");
        database.setDatabaseName(QApplication::applicationDirPath()+"account.db");
    }
    else
    {
        fclose(f1);
        //数据库存在
        //跳过创建数据库的步骤
        QSqlDatabase database =QSqlDatabase::addDatabase("ACCOUNT_AND_PASSWORD");
        database.setDatabaseName(QApplication::applicationDirPath()+"account.db");
    }
}

bool SqliteOperator_user_account::openDb()
{
    if(!database.open())
    {
        qDebug()<<"ERROR:FAILED TO CONNECT DATABASE"<<database.lastError();
        return false;
    }
    else
    {
        return true;
    }
}

void SqliteOperator_user_account::createTable()
{
    //创建数据表
    //在下方创建需要执行的SQL语句的对象
    QSqlQuery sqlQuery;
    QString createSql=QString("CREATE TABLE ACCOUNT_AND_PASSWORD(\
                                ACCOUNT TEXT PRIMARY KEY NOT NULL,\
                                PASSWORD TEXT NOT NULL)");
    //准备执行SQL语句
    sqlQuery.prepare(createSql);
    //执行SQL语句
    if(!sqlQuery.exec())
    {
        qDebug()<<"ERROR : FAIL TO CREATE TABLE"<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"Table created successfully";
    }
}

bool SqliteOperator_user_account::isTableExisted_login(QString& ACCOUNT,QString& PASSWORD)
{
    QSqlQuery query;
    query.exec(QString("SELECT * from ACCOUNT_AND_PASSWORD WHERE ACCOUNT = '%1' AND PASSWORD = '%2'").arg(ACCOUNT).arg(PASSWORD));
    if(!query.next())
    {
        qDebug()<<"The information is not existed";
        return false;
    }
    else
    {
        qDebug()<<"The information is existed";
        return true;
    }
}

bool SqliteOperator_user_account::isTableExisted_register(QString& account)
{
    QSqlQuery query;
    query.exec(QString("SELECT * from ACCOUNT_AND_PASSWORD WHERE ACCOUNT = '%1'").arg(account));
    if(!query.next())
    {
        qDebug()<<"The information is not existed";
        return false;
    }
    else
    {
        qDebug()<<"The information is existed";
        return true;
    }
}

void SqliteOperator_user_account::insertData(user_account &data)
{
    QSqlQuery query;

}
