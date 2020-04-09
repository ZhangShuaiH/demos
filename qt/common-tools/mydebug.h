#ifndef MYDEBUG_H
#define MYDEBUG_H
#include <QDebug>
/**
* @brief ���ڵ��Գ���
* @version 1.0
* @date 2018-05-11 ����
* @author ZhangShuai
**/
#define myDebug(x)      qDebug()<< "Debug "<< __FUNCTION__ <<__LINE__<< "]:"<<x
//#define qDebug if(false)qDebug // ���� debug ��Ϣ

#endif // MYDEBUG_H


/***demo**************
#include "mydebug.h"

int main(){
    myDebug("main ����������");// Debug  main 23 ]: main ����������
    myDebug("");
    myDebug(QString("sdfasdgg"));// �ַ���
    myDebug(QStringList());// �ַ����б�
    myDebug(QVariant());// ����
    myDebug(123);// ����
}
**********************/
