#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

struct USER_ACCOUNT
{
    QString ACCOUNT;        //用户名
    QString PASSWORD;       //密码
};

struct PATIENT_INFO
{
    QString name;           //患者姓名
    QString gender;         //患者性别
    QString age;            //患者年龄
    QString time;           //就诊时间
    QString part;           //患病部位
    QString bad;            //不良嗜好
};

struct SPECTRUM_INFO
{
    int id;
    QString name;           //病人信息
    float data[1044];       //光谱的点数<信息储存>
};

USER_ACCOUNT user_account;
PATIENT_INFO patient_info;
SPECTRUM_INFO Spectrum_info;

class SqliteOperator_user_account
{
public:
    SqliteOperator_user_account();
    //打开数据库
    bool openDb(void);
    //创建数据表
    void createTable(void);
    //判断数据是否存在
    bool isTableExisted_register(QString& account);      //用于注册时检测是否有相同的用户名
    //判断用户名和密码是否能够在数据库中成功匹配
    bool isTableExisted_login(QString& account,QString& password);  //用于判断用户名和密码是否正确
    //插入数据
    void insertData(USER_ACCOUNT data);
    //修改数据
    void modifyData(QString ACCOUNT,QString PASSWORD);
    //删除数据表
    void deleteTable(QString tableName);
    //关闭数据库
    void closeDb(void);
private:
    QSqlDatabase database;//用于建立宇数据库的链接
};

class SqliteOperator_patient_info
{
public:
    SqliteOperator_patient_info();
    //打开数据库
    bool openDb(void);
    //创建数据表
    bool createTable(void);
    //判断数据是否存在
    bool isTableExisted_patient(QString &name);     //判断病人是否存在于数据库中
    //插入数据
    void singleInsertData(PATIENT_INFO patient);
    //修改数据
    void modifyData(PATIENT_INFO patient);
    //删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString tableName);
    //关闭数据库
    void closeDb(void);
private:
    QSqlDatabase database;        //建立和数据库的链接
};

class SqliteOperator_Spectrum_info
{
public:
    SqliteOperator_Spectrum_info();
    //打开数据库
    bool openDb(void);
    //创建数据表
    bool createTable(void);
    //判断数据表是否存在
    bool isTableExist(QString tableName);
    //插入数据
    void singleInsertData(SPECTRUM_INFO data);
    //修改数据
    void modifyData(SPECTRUM_INFO data);
    //删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString tableName);
    //关闭数据库
    void closeDb(void);
private:
    QSqlDatabase database;          //用于建立和数据库的链接
};

#endif // SQLITEOPERATOR_H
