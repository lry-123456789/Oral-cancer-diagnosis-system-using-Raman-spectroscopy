#include "SqliteOperator.h"
#include <stdio.h>
#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets/QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlDriver>

#include <QMessageBox>

#include <string>

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
        //QSqlDatabase
        database =QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("account.db");
        QSqlQuery query=QSqlQuery(database);
        query.prepare("insert into ACCOUNT_AND_PASSWORD (ACCOUNT, PASSWORD) values (?,?);");
        query.addBindValue("1111");
        query.addBindValue("1111");
        //query.exec();
        if(!query.exec())
        {
            qDebug()<<"FAILED TO INSERT DATA"<<Qt::endl;
        }
        else
        {
            qDebug()<<"insert successfully"<<Qt::endl;
        }
        //database.close();
    }
    else
    {
        fclose(f1);
        //数据库存在
        //跳过创建数据库的步骤
        //QSqlDatabase
        database =QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("account.db");
        qDebug()<<"the table is existed"<<Qt::endl;
        QSqlQuery query=QSqlQuery(database);
        query.prepare("insert into ACCOUNT_AND_PASSWORD (ACCOUNT, PASSWORD) values (?,?);");
        query.addBindValue("11111");
        query.addBindValue("11111");
        query.exec();
        if(!query.exec())
        {
            qDebug()<<"FAILED TO INSERT DATA"<<Qt::endl;
        }
        else
        {
            qDebug()<<"insert successfully"<<Qt::endl;
        }
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
    QSqlQuery sqlQuery=QSqlQuery(database);
    //QSqlQuery sqlQuery=QSqlQuery::QSqlQuery(database);
    database.open();
    QString createSql=QString("CREATE TABLE ACCOUNT_AND_PASSWORD(ACCOUNT TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL)");
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
    /*
    sqlQuery.prepare("insert into ACCOUNT_AND_PASSWORD (ACCOUNT, PASSWORD) values (?,?);");
    sqlQuery.addBindValue("1111");
    sqlQuery.addBindValue("1111");
    //query.exec();
    if(!sqlQuery.exec())
    {
        qDebug()<<"FAILED TO INSERT DATA"<<Qt::endl;
    }
    else
    {
        qDebug()<<"insert successfully"<<Qt::endl;
    }
    */
}

bool SqliteOperator_user_account::isTableExisted_login(QString& ACCOUNT,QString& PASSWORD)
{
    QSqlQuery query=QSqlQuery(database);
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
    QSqlQuery query=QSqlQuery(database);
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

void SqliteOperator_user_account::insertData(USER_ACCOUNT data)
{
    QSqlQuery query=QSqlQuery(database);
    /*
    query.prepare("INSERT INTO ACCOUNT_AND_PASSWORD (ACCOUNT, PASSWORD)"
                  "VALUES (:ACCOUNT,:PASSWORD)");
                  */
    query.prepare("insert into ACCOUNT_AND_PASSWORD(ACCOUNT, PASSWORD) values (?,? )");
    //query.bindValue(":ACCOUNT","111111111111");
    //query.bindValue(":PASSWORD","1111111111111");
    //qDebug()<<"ACCOUNT\t:"<<data.ACCOUNT;
    //qDebug()<<"PASSWORD\t:"<<data.PASSWORD;
    //query.addBindValue("1111");
    //query.addBindValue("111");
    query.addBindValue(data.ACCOUNT);
    query.addBindValue(data.PASSWORD);
    if(!query.exec())
    {
        qDebug()<<"FAILED TO INSERT DATA"<<Qt::endl;
    }
    else
    {
        qDebug()<<"insert successfully"<<Qt::endl;
    }
}

void SqliteOperator_user_account::modifyData(QString ACCOUNT,QString PASSWORD)
{
    QSqlQuery query=QSqlQuery(database);
    query.prepare("UPDATE ACCOUNT_AND_PASSWORD SET ACCOUNT=?,PASSWORD=?");
    query.addBindValue(ACCOUNT);
    query.addBindValue(PASSWORD);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"update data successfully";
    }
}

void SqliteOperator_user_account::deleteTable(QString tableName)
{
    QSqlQuery query=QSqlQuery(database);
    query.exec(QString("DROP TABLE %1").arg(tableName));
    if(query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"delete table success";
    }
}

void SqliteOperator_user_account::closeDb(void)
{
    database.close();
}

SqliteOperator_patient_info::SqliteOperator_patient_info()
{
    FILE *f1=fopen("patient_info.db","rb");
    if(f1==NULL)
    {
        //数据库不存在
        //创建数据库
        database =QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("patient_info.db");
        QSqlQuery query=QSqlQuery(database);
        /*
        QString createSql =QString("CREATE TABLE PATIENT_INFO(\
                                    NAME TEXT PRIMARY NOT NULL,\
                                    GENDER TEXT NOT NULL,\
                                    AGE TEXT NOT NULL,\
                                    TIME TEXT NOT NULL,\
                                    PART TEXT ,\
                                    BAD TEXT");
                                    */
        //QString createSql =QString("insert into PATIENT_INFO(NAME, GENDER, AGE, TIME, PART, BAD) values(?,?,?,?,?,?)");
        //QString createSql=QString("CREATE TABLE ACCOUNT_AND_PASSWORD(ACCOUNT TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL)");
        /*
         *
        query.prepare("insert into ACCOUNT_AND_PASSWORD (ACCOUNT, PASSWORD) values (?,?);");
        query.addBindValue("1111");
        query.addBindValue("1111");
        //query.exec();
        if(!query.exec())
        {
            qDebug()<<"FAILED TO INSERT DATA"<<Qt::endl;
        }
        else
        {
            qDebug()<<"insert successfully"<<Qt::endl;
        }
        */
        query.prepare("insert into PATIENT_INFO(NAME, GENDER, AGE, TIME, PART, BAD) values(?,?,?,?,?,?)");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        //query.prepare(createSql);
        //执行语句
        if(!query.exec())
        {
            qDebug()<<"ERROR Failed to create table"<<query.lastError();
            //return false;
        }
        else
        {
            qDebug()<<"Table created"<<Qt::endl;
            //return false;
        }
    }
    else
    {
        fclose(f1);
        //数据库存在
        //跳过创建数据库的步骤
        qDebug()<<"table existed"<<Qt::endl;
        database =QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("patient_info.db");
        QSqlQuery query=QSqlQuery(database);
        /*
        QString createSql =QString("CREATE TABLE PATIENT_INFO(\
                                    NAME TEXT PRIMARY NOT NULL,\
                                    GENDER TEXT NOT NULL,\
                                    AGE TEXT NOT NULL,\
                                    TIME TEXT NOT NULL,\
                                    PART TEXT ,\
                                    BAD TEXT");
                                    */
        //QString createSql =QString("CREATE TABLE PATIENT_INFO(NAME TEXT PRIMARY NOT NULL, GENDER TEXT NOT NULL, AGE TEXT NOT NULL, TIME TEXT NOT NULL, PART TEXT , BAD TEXT)");
        //QSqlQuery query=QSqlQuery(database);
        /*
        QString createSql =QString("CREATE TABLE PATIENT_INFO(\
                                    NAME TEXT PRIMARY NOT NULL,\
                                    GENDER TEXT NOT NULL,\
                                    AGE TEXT NOT NULL,\
                                    TIME TEXT NOT NULL,\
                                    PART TEXT ,\
                                    BAD TEXT");
                                    */
        //QString createSql =QString("CREATE TABLE PATIENT_INFO(NAME TEXT PRIMARY NOT NULL, GENDER TEXT NOT NULL, AGE TEXT NOT NULL, TIME TEXT NOT NULL, PART TEXT, BAD TEXT)");
        QString createSql =QString("insert into PATIENT_INFO(NAME, GENDER, AGE, TIME, PART, BAD) values(?,?,?,?,?,?)");
        //QString createSql=QString("CREATE TABLE ACCOUNT_AND_PASSWORD(ACCOUNT TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL)");
        /*
         *
        query.prepare("insert into ACCOUNT_AND_PASSWORD (ACCOUNT, PASSWORD) values (?,?);");
        query.addBindValue("1111");
        query.addBindValue("1111");
        //query.exec();
        if(!query.exec())
        {
            qDebug()<<"FAILED TO INSERT DATA"<<Qt::endl;
        }
        else
        {
            qDebug()<<"insert successfully"<<Qt::endl;
        }
        */
        query.prepare("insert into PATIENT_INFO(NAME, GENDER, AGE, TIME, PART, BAD) values(?,?,?,?,?,?)");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        query.addBindValue("111");
        //query.prepare(createSql);
        //执行语句
        if(!query.exec())
        {
            qDebug()<<"ERROR Failed to create table"<<query.lastError();
            //return false;
        }
        else
        {
            qDebug()<<"Table created"<<Qt::endl;
            //return false;
        }
    }
}

bool SqliteOperator_patient_info::openDb(void)
{
    if(!database.open())
    {
        qDebug()<<"ERROR : Failed to connect database"<<database.lastError();
        return false;
    }
    else
    {
        qDebug()<<"Successfully connect database";
        return true;
    }
}

bool SqliteOperator_patient_info::createTable(void)
{
    QSqlQuery query=QSqlQuery(database);
    database.open();
    QString createSql =QString("CREATE TABLE PATIENT_INFO(NAME TEXT PRIMARY KEY NOT NULL, GENDER TEXT NOT NULL, AGE TEXT NOT NULL, TIME TEXT NOT NULL, PART TEXT, BAD TEXT)");

    query.prepare(createSql);
    //执行语句
    if(!query.exec())
    {
        qDebug()<<"ERROR Failed to create table"<<query.lastError();
        return false;
    }
    else
    {
        qDebug()<<"Table created"<<Qt::endl;
        return false;
    }
}

bool SqliteOperator_patient_info::isTableExisted_patient(QString& tableName)
{
    database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }
    return false;
}

void SqliteOperator_patient_info::singleInsertData(PATIENT_INFO patient)
{
    QSqlQuery query=QSqlQuery(database);
    database.open();
    query.prepare("insert into PATIENT_INFO(NAME, GENDER, AGE, TIME, PART, BAD) values (?,?,?,?,?,?);");
    query.addBindValue(patient.name);
    query.addBindValue(patient.gender);
    query.addBindValue(patient.age);
    query.addBindValue(patient.time);
    query.addBindValue(patient.part);
    query.addBindValue(patient.bad);
    //query.addBindValue("11111");
    //query.addBindValue("11111");
    //query.addBindValue("11111");
    //query.addBindValue("11111");
    //query.addBindValue("11111");
    //query.addBindValue("11111");
    //query.prepare("insert into ACCOUNT_AND_PASSWORD(ACCOUNT, PASSWORD) values (?,? )");
    //query.bindValue(":ACCOUNT","111111111111");
    //query.bindValue(":PASSWORD","1111111111111");
    //qDebug()<<"ACCOUNT\t:"<<data.ACCOUNT;
    //qDebug()<<"PASSWORD\t:"<<data.PASSWORD;
    //query.addBindValue("1111");
    //query.addBindValue("111");
    qDebug()<<"name="<<patient.name<<"gender="<<patient.gender<<"age="<<patient.age<<"time="<<patient.time<<"part="<<patient.part<<"bad="<<patient.bad;
    if(!query.exec())
    {
        qDebug()<<"error: failed to insert data"<<query.lastError();
    }
    else
    {
        qDebug()<<"insert data successfully"<<Qt::endl;
    }
}

void SqliteOperator_patient_info::modifyData(PATIENT_INFO patient)
{
    QSqlQuery query=QSqlQuery(database);
    query.prepare("UPDATE PATIENT_INFO NAME=?,GENDER=?,AGE=?,TIME=?,PART=?,BAD=?");
    query.addBindValue(patient.name);
    query.addBindValue(patient.gender);
    query.addBindValue(patient.age);
    query.addBindValue(patient.time);
    query.addBindValue(patient.part);
    query.addBindValue(patient.bad);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"update data success!";
    }
}

void SqliteOperator_patient_info::deleteData(int id)
{
    QSqlQuery query=QSqlQuery(database);
    query.exec(QString("DELTET FROM PATIENT_INFO WHERE id='%1'").arg(id));
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"DALETE DATA SUCCESS";
    }
}

void SqliteOperator_patient_info::deleteTable(QString tableName)
{
    QSqlQuery query=QSqlQuery(database);
    query.exec(QString("DROP TABLE %1").arg(tableName));
    if(!query.exec())
    {
        qDebug()<<"FAILED:"<<query.lastError();
    }
    else
    {
        qDebug()<<"DELETE TABLE SUCCESS";
    }
}

void SqliteOperator_patient_info::closeDb(void)
{
    database.close();
}

SqliteOperator_Spectrum_info::SqliteOperator_Spectrum_info()
{
    FILE *f1=fopen("spectrum.db","rb");
    if(f1==NULL)
    {
        //数据库不存在
        //创建数据库
        database =QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(QApplication::applicationDirPath()+"spectrum.db");
    }
    else
    {
        fclose(f1);
        //数据库存在
        //跳过创建数据库的步骤
        database =QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(QApplication::applicationDirPath()+"spectrum.db");
    }
}

bool SqliteOperator_Spectrum_info::openDb(void)
{
    if(!database.open())
    {
        qDebug()<<"ERROR : Failed to connect database"<<database.lastError();
        return false;
    }
    else
    {
        qDebug()<<"Successfully connect database";
        return true;
    }
}

bool SqliteOperator_Spectrum_info::createTable(void)
{
    QSqlQuery query=QSqlQuery(database);
    QString createSql =QString("CREATE TABLE SPECTRUM(NAME TEXT PRIMARY KRY NOT NULL, DATA TEXT NOT NULL");
    query.prepare(createSql);
    //开始执行SQL语句
    if(!query.exec())
    {
        qDebug()<<"ERROR : Failed to create table"<<query.lastError();
    }
    else
    {
        qDebug()<<"table created successfully";
    }
}

bool SqliteOperator_Spectrum_info::isTableExist(QString tableName)
{
    database=QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }
    return false;
}

void SqliteOperator_Spectrum_info::singleInsertData(SPECTRUM_INFO data)
{
    QByteArray data_0;
    int i=0;
    for(i=0;i<1044;i++)
    {
        data_0.append(data.data[i]);
    }
    std::string data_1=data_0.toStdString();
    QString data_2=QString::fromStdString(data_1);
    //下面进行数据库的操作
    QSqlQuery query=QSqlQuery(database);
    query.prepare("INSERT INTO SPECTRUM VALUES(:NAME,:DATA)");
    query.bindValue(":NAME",data.name);
    query.bindValue(":GENDER",data_2);
    if(!query.exec())
    {
        qDebug()<<"error: failed to insert data"<<query.lastError();
    }
    else
    {
        qDebug()<<"insert data successfully"<<Qt::endl;
    }
}

void SqliteOperator_Spectrum_info::modifyData(SPECTRUM_INFO data)
{
    QByteArray data_0;
    int i=0;
    for(i=0;i<1044;i++)
    {
        data_0.append(data.data[i]);
    }
    std::string data_1=data_0.toStdString();
    QString data_2=QString::fromStdString(data_1);
    QSqlQuery query=QSqlQuery(database);
    query .prepare("UPDATE SPECTRUM SET NAME=?,DATA=?");
    query.addBindValue(data.name);
    query.addBindValue(data_2);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"updated data success";
    }
}

void SqliteOperator_Spectrum_info::deleteData(int id)
{
    QSqlQuery query=QSqlQuery(database);
    query.exec(QString("DELETE FROM SPECTRUM WHERE id=%1").arg(id));
    if(!query.exec())
    {
        qDebug()<<"FAILED:"<<query.lastError();
    }
    else
    {
        qDebug()<<"deleted data successfully";
    }
}

void SqliteOperator_Spectrum_info::deleteTable(QString tableName)
{
    QSqlQuery query=QSqlQuery(database);
    query.exec(QString("DROP TABLE %1").arg(tableName));
    if(query.exec())
    {
        qDebug()<<"FAILED:"<<query.lastError();
    }
    else
    {
        qDebug()<<"delete the table successfully";
    }
}

void SqliteOperator_Spectrum_info::closeDb(void)
{
    database.close();
}
