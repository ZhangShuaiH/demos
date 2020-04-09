#ifndef MYSQL_H
#define MYSQL_H
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "mydebug.h"

/// 数据库接口
class Mysql
{
public:
    Mysql();
    ~Mysql();
    static QSqlDatabase getDatabase(const QString dbName);
    static QSqlDatabase getDatabase(const QString connName, const QString userName, const QString password, const QString dbName);
    static QSqlQuery getAndExecuteQuery(const QString dbName, const QString sql);
    static QSqlQuery getAndExecuteQuery(QSqlDatabase db, const QString sql);
    static QSqlQuery getQuery(const QString dbName);
    static QSqlQuery getQuery(QSqlDatabase db);
    static bool executeQuery(QSqlQuery &query, const QString sql);
    static bool executeSql(const QString dbName, const QString sql);
    static bool executeSql(QSqlDatabase db, const QString sql);

private:
    void test();
};

#endif // MYSQL_H
