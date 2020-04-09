#ifndef COMMONTOOL_H
#define COMMONTOOL_H

#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <iostream>
using namespace std;

#define myDebug(x)      qDebug()<< "Debug "<< __FUNCTION__ <<__LINE__<< "]:"<<x
#define myWarning(x)    (qWarning()<< "Warning "<<__FUNCTION__<<__LINE__<< "]:" << x)
#define myFatal(x)      (qWarning()<< "Fatal "    <<__FUNCTION__ <<__LINE__<< "]:" << x)
//#define myFatal(x)      (qFatal()<< "Fatal "    <<__FUNCTION__ <<__LINE__<< "]:" << x)

//#define qDebug if(false)qDebug // фа╠н debug пео╒

#endif // COMMONTOOL_H
