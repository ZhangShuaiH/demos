#include "mysql.h"

/**
* @brief ���ݿ�ӿ�
* @date ���� 2018-03-15
* @date 2018-03-19 ��Ӻ���: executeQuery()
* @date 2018-03-19 �޸ĺ���: getAndExecuteQuery()
* @date 2018-03-19 ��Ӻ���: executeSql()
* @date 2018-05-14 ��Ӻ���: connectDB()
* @date 2018-05-15 ��Ӻ���: executeSql(QSqlDatabase db, const QString sql)
* @date 2018-05-15 ��Ӻ���: QSqlQuery getAndExecuteQuery(QSqlDatabase db, const QString sql)
* @version 1.0.2
* @author ZhangShuai
**/
Mysql::Mysql()
{

}

/**
* @brief ��ȡ Database ����
* @param dbName: ���ݿ�����
* @return db: ���ݿ���
* @date 2018-03-15
**/
QSqlDatabase Mysql::getDatabase(QString dbName){
    return getDatabase("mydb", "root", "root", dbName);
}
/**
* @brief �����������ݿ���
* @param connName: ��������
* @param userName: �û�����
* @param password: ����
* @param dbName: ���ݿ�����
* @return db: ���ݿ���
* @date 2018-05-14 ����
**/
QSqlDatabase Mysql::getDatabase(const QString connName, const QString userName, const QString password, const QString dbName)
{
    QSqlDatabase db;
    QString hostName = "localhost";
    int port = 3306;
    db = QSqlDatabase::addDatabase("QMYSQL", connName);
    /// ����������
    db.setHostName(hostName);//��������
    /// �������ݿ���
    db.setDatabaseName(dbName);//���ݿ�����
    /// ��������
    db.setPassword(password);
    /// �����û���
    db.setUserName(userName);
    /// ���ö˿ں�
    db.setPort(port);
    /// �����ݿ�
    if(!db.isOpen() && !db.open()){ // ����������ݿ�ʧ��, ���ص� db, ���޷��鵽����
        /// �����ʧ��, ����������Ϣ
        QMessageBox::warning(0, "����", "���ݿ��ʧ��!");
    }else {

    }
    /// ���� db
    return db;
}
/**
* @brief ��ȡ��ִ�� query
* @param[in] dbname ���ݿ���,�����������ݿ�
* @param[in] sql sql ���
* @return query: ���ڵõ����
* @note �������ɶ���ʹ��
* @date ���� 2018-03-15
* @version 1.0
**/
QSqlQuery Mysql::getAndExecuteQuery(const QString dbName, const QString sql)
{
    /// �������� db
    QSqlDatabase db = getDatabase(dbName);
    /// �������� query
    QSqlQuery query(db);
    /// ִ�� sql
    executeQuery(query, sql);
    /// ���� query
    return query;
}
/**
* @brief ��ȡ��ִ�� query
* @param[in] db ���ݿ��������ڴ��� querry
* @param[in] sql sql ���
* @return query: ���ڵõ����
* @date 2018-05-15 ����
**/
QSqlQuery Mysql::getAndExecuteQuery(QSqlDatabase db, const QString sql)
{
    /// �������� query
    QSqlQuery query(db);
    /// ִ�� sql
    executeQuery(query, sql);
    /// ���� query
    return query;
}
/**
* @brief ��ȡ QSqlQuery ����
* @param[in] dbName ���ݿ�����
* @date 2018-03-23 ����
**/
QSqlQuery Mysql::getQuery(const QString dbName)
{
    /// �������� db getDatabase()
    QSqlDatabase db = getDatabase(dbName);
    /// �������� query
    QSqlQuery query(db);
    /// ���� query
    return query;
}
/**
* @brief ��ȡ QSqlQuery ����
* @param[in] db ���ݿ����
* @date 2018-05-17 ����
**/
QSqlQuery Mysql::getQuery(QSqlDatabase db)
{
        QSqlQuery query(db);
        return query;
}
/**
* @brief ִ�� sql ���
* @param[in] dbName ���ݿ�����
* @param[in] sql sql ���
* @return true|false
* @date 2018-03-19 ����
**/
bool Mysql::executeSql(const QString dbName, const QString sql){
    /// �������� QSqlDatabase
    QSqlDatabase db = getDatabase(dbName);
    /// �������� QSqlQuery
    QSqlQuery query(db);
    /// ִ�� sql
    return executeQuery(query, sql);
}
/**
* @brief ִ�� sql ���
* @param[in] db ���ݿ���
* @param[in] sql sql ���
* @return true|false
* @date 2018-05-15 ����
**/
bool Mysql::executeSql(QSqlDatabase db, const QString sql){
    /// �������� QSqlQuery
    QSqlQuery query(db);
    /// ִ�� sql
    return executeQuery(query, sql);
}

/**
* @brief ִ�� query
* @param[in] query
* @param[in] sql
* @return true|false
* @date ���� 2018-03-15
* @version 1.0
**/
bool Mysql::executeQuery(QSqlQuery &query, const QString sql)
{
    /// ��� sql
    myDebug(sql);
    /// ִ�� sql
    if(!query.exec(sql)){
        /// ���ִ�д���, ���������������Ϣ
        QMessageBox::warning(0, "sql error", query.lastError().text());
        myDebug(query.lastError().text());
        return false;
    }
    return true;
}

/**
* @brief ���Ժ���, ��ɾ
* @date 2018-03-19 ����
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
