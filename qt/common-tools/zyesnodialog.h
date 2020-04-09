#ifndef ZYESNODIALOG_H
#define ZYESNODIALOG_H

#include <QString>
#include <QMessageBox>

class ZYesNoDialog
{
public:
    ZYesNoDialog();
    static bool noIconResult(QString title, QString text);
    static bool questionResult(QString title, QString text);
    static bool infoResult(QString title, QString text);
    static bool warnResult(QString title, QString text);
    static bool criticalResult(QString title, QString text);

private:
    static bool result(QMessageBox::Icon icon, QString title, QString text);
};

#endif // ZYESNODIALOG_H
