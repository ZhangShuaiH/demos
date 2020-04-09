#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "mydebug.h"
#include <QRegExp>
#include <QString>
class Calculator
{
public:
    Calculator();
    QString bigRealNumberMultiply(QString a, QString b);
    QString bigRealNumberAdd(QString a, QString b);
    void test();

private:
    QChar getSymbol(QString &readNumber);
    void appendPoint(QString &readNumber);
    void align(QString &a, QString &b);
    int compare(const QString &a, const QString &b);
    void test_addRealNumber0();
    void test_addRealNumber1();
    void test_multiply0();
    void test_multiply1();
    void test_compare();
};

#endif // CALCULATOR_H
