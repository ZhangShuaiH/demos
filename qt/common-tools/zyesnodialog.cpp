#include "zyesnodialog.h"

/**
* @brief ���� QMessageBox С����, �������û�����İ�ť
* @date 2018-03-29 ����
* @version 1.0.0
* @author ZhangShuai
**/
ZYesNoDialog::ZYesNoDialog()
{

}
/**
* @brief ��������, �����û�����İ�ť
* @param[in] icon ͼ��
* @param[in] title ����
* @param[in] text �ı�
* @return true|false ȷ��|ȡ��
* @date 2018-03-29 ����
**/
bool ZYesNoDialog::result(QMessageBox::Icon icon, QString title, QString text)
{
    QMessageBox box(icon,title,text,QMessageBox::Yes|QMessageBox::No);
    box.setButtonText(QMessageBox::Yes, "ȷ��");
    box.setButtonText(QMessageBox::No, "ȡ��");
    if (box.exec()==QMessageBox::Yes)
        return true;
    return false;
}
/**
* @brief ������ͼ�괰��, �����û�����İ�ť
* @see result()
* @param[in] title ����
* @param[in] text �ı�
* @return true|false ȷ��|ȡ��
* @date 2018-03-29 ����
**/
bool ZYesNoDialog::noIconResult(QString title, QString text)
{
    return result(QMessageBox::NoIcon, title, text);
}
/**
* @brief �������ⴰ��, �����û�����İ�ť
* @see result()
* @param[in] title ����
* @param[in] text �ı�
* @return true|false ȷ��|ȡ��
* @date 2018-03-29 ����
**/
bool ZYesNoDialog::questionResult(QString title, QString text)
{
    return result(QMessageBox::Question, title, text);
}
/**
* @brief ������Ϣ����, �����û�����İ�ť
* @see result()
* @param[in] title ����
* @param[in] text �ı�
* @return true|false ȷ��|ȡ��
* @date 2018-03-29 ����
**/
bool ZYesNoDialog::infoResult(QString title, QString text)
{
    return result(QMessageBox::Information, title, text);
}
/**
* @brief �������洰��, �����û�����İ�ť
* @see result()
* @param[in] title ����
* @param[in] text �ı�
* @return true|false ȷ��|ȡ��
* @date 2018-03-29 ����
**/
bool ZYesNoDialog::warnResult(QString title, QString text)
{
    return result(QMessageBox::Warning, title, text);
}
/**
* @brief �������ش��󴰿�, �����û�����İ�ť
* @see result()
* @param[in] title ����
* @param[in] text �ı�
* @return true|false ȷ��|ȡ��
* @date 2018-03-29 ����
**/
bool ZYesNoDialog::criticalResult(QString title, QString text)
{
    return result(QMessageBox::Critical, title, text);
}
