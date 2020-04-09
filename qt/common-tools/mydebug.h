#ifndef MYDEBUG_H
#define MYDEBUG_H
#include <QDebug>
/**
* @brief 用于调试程序
* @version 1.0
* @date 2018-05-11 创建
* @author ZhangShuai
**/
#define myDebug(x)      qDebug()<< "Debug "<< __FUNCTION__ <<__LINE__<< "]:"<<x
//#define qDebug if(false)qDebug // 屏蔽 debug 信息

#endif // MYDEBUG_H


/***demo**************
#include "mydebug.h"

int main(){
    myDebug("main 函数被调用");// Debug  main 23 ]: main 函数被调用
    myDebug("");
    myDebug(QString("sdfasdgg"));// 字符串
    myDebug(QStringList());// 字符串列表
    myDebug(QVariant());// 变量
    myDebug(123);// 数字
}
**********************/
