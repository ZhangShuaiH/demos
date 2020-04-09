#include "mysql.h"

/**
* @brief 数据库接口
* @date 创建 2018-03-15
* @date 2018-03-19 添加函数: executeQuery()
* @date 2018-03-19 修改函数: getAndExecuteQuery()
* @date 2018-03-19 添加函数: executeSql()
* @date 2018-05-14 添加函数: connectDB()
* @date 2018-05-15 添加函数: executeSql(QSqlDatabase db, const QString sql)
* @date 2018-05-15 添加函数: QSqlQuery getAndExecuteQuery(QSqlDatabase db, const QString sql)
* @version 1.0.2
* @author ZhangShuai
**/
Mysql::Mysql()
{

}

/**
* @brief 获取 Database 对象
* @param dbName: 数据库名称
* @return db: 数据库句柄
* @date 2018-03-15
**/
QSqlDatabase Mysql::getDatabase(QString dbName){
    return getDatabase("mydb", "root", "root", dbName);
}
/**
* @brief 用于生成数据库句柄
* @param connName: 连接名称
* @param userName: 用户名称
* @param password: 密码
* @param dbName: 数据库名称
* @return db: 数据库句柄
* @date 2018-05-14 创建
**/
QSqlDatabase Mysql::getDatabase(const QString connName, const QString userName, const QString password, const QString dbName)
{
    QSqlDatabase db;
    QString hostName = "localhost";
    int port = 3306;
    db = QSqlDatabase::addDatabase("QMYSQL", connName);
    /// 设置主机名
    db.setHostName(hostName);//主机名字
    /// 设置数据库名
    db.setDatabaseName(dbName);//数据库名字
    /// 设置密码
    db.setPassword(password);
    /// 设置用户名
    db.setUserName(userName);
    /// 设置端口号
    db.setPort(port);
    /// 打开数据库
    if(!db.isOpen() && !db.open()){ // 如果连接数据库失败, 返回的 db, 将无法查到数据
        /// 如果打开失败, 弹出错误信息
        QMessageBox::warning(0, "错误", "数据库打开失败!");
    }else {

    }
    /// 返回 db
    return db;
}
/**
* @brief 获取并执行 query
* @param[in] dbname 数据库名,用于连接数据库
* @param[in] sql sql 语句
* @return query: 用于得到结果
* @note 本函数可独立使用
* @date 创建 2018-03-15
* @version 1.0
**/
QSqlQuery Mysql::getAndExecuteQuery(const QString dbName, const QString sql)
{
    /// 创建对象 db
    QSqlDatabase db = getDatabase(dbName);
    /// 创建对象 query
    QSqlQuery query(db);
    /// 执行 sql
    executeQuery(query, sql);
    /// 返回 query
    return query;
}
/**
* @brief 获取并执行 query
* @param[in] db 数据库句柄，用于创建 querry
* @param[in] sql sql 语句
* @return query: 用于得到结果
* @date 2018-05-15 创建
**/
QSqlQuery Mysql::getAndExecuteQuery(QSqlDatabase db, const QString sql)
{
    /// 创建对象 query
    QSqlQuery query(db);
    /// 执行 sql
    executeQuery(query, sql);
    /// 返回 query
    return query;
}
/**
* @brief 获取 QSqlQuery 对象
* @param[in] dbName 数据库名称
* @date 2018-03-23 创建
**/
QSqlQuery Mysql::getQuery(const QString dbName)
{
    /// 创建对象 db getDatabase()
    QSqlDatabase db = getDatabase(dbName);
    /// 创建对象 query
    QSqlQuery query(db);
    /// 返回 query
    return query;
}
/**
* @brief 获取 QSqlQuery 对象
* @param[in] db 数据库对象
* @date 2018-05-17 创建
**/
QSqlQuery Mysql::getQuery(QSqlDatabase db)
{
        QSqlQuery query(db);
        return query;
}
/**
* @brief 执行 sql 语句
* @param[in] dbName 数据库名称
* @param[in] sql sql 语句
* @return true|false
* @date 2018-03-19 创建
**/
bool Mysql::executeSql(const QString dbName, const QString sql){
    /// 创建对象 QSqlDatabase
    QSqlDatabase db = getDatabase(dbName);
    /// 创建对象 QSqlQuery
    QSqlQuery query(db);
    /// 执行 sql
    return executeQuery(query, sql);
}
/**
* @brief 执行 sql 语句
* @param[in] db 数据库句柄
* @param[in] sql sql 语句
* @return true|false
* @date 2018-05-15 创建
**/
bool Mysql::executeSql(QSqlDatabase db, const QString sql){
    /// 创建对象 QSqlQuery
    QSqlQuery query(db);
    /// 执行 sql
    return executeQuery(query, sql);
}

/**
* @brief 执行 query
* @param[in] query
* @param[in] sql
* @return true|false
* @date 创建 2018-03-15
* @version 1.0
**/
bool Mysql::executeQuery(QSqlQuery &query, const QString sql)
{
    /// 输出 sql
    myDebug(sql);
    /// 执行 sql
    if(!query.exec(sql)){
        /// 如果执行错误, 弹窗并输出错误信息
        QMessageBox::warning(0, "sql error", query.lastError().text());
        myDebug(query.lastError().text());
        return false;
    }
    return true;
}

/**
* @brief 测试函数, 可删
* @date 2018-03-19 创建
**/
void Mysql::test(){
    QSqlDatabase db = getDatabase("fiveprevention");

    QSqlQuery query(db);
    QString sql = "SELECT * from taskoperation";
    query.exec(sql);
    while (query.next()) {
        QMessageBox::warning(0, "query", query.value(0).toString());
        QMessageBox::warning(0, "query", query.value(1).toString());
        QMessageBox::warning(0, "query", query.value(2).toString());
        QMessageBox::warning(0, "query", query.value(3).toString());
    }
}

Mysql::~Mysql()
{

}
