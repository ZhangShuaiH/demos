#include "zyesnodialog.h"

/**
* @brief 弹出 QMessageBox 小窗口, 并监听用户点击的按钮
* @date 2018-03-29 创建
* @version 1.0.0
* @author ZhangShuai
**/
ZYesNoDialog::ZYesNoDialog()
{

}
/**
* @brief 弹出窗口, 监听用户点击的按钮
* @param[in] icon 图标
* @param[in] title 标题
* @param[in] text 文本
* @return true|false 确定|取消
* @date 2018-03-29 创建
**/
bool ZYesNoDialog::result(QMessageBox::Icon icon, QString title, QString text)
{
    QMessageBox box(icon,title,text,QMessageBox::Yes|QMessageBox::No);
    box.setButtonText(QMessageBox::Yes, "确定");
    box.setButtonText(QMessageBox::No, "取消");
    if (box.exec()==QMessageBox::Yes)
        return true;
    return false;
}
/**
* @brief 弹出无图标窗口, 监听用户点击的按钮
* @see result()
* @param[in] title 标题
* @param[in] text 文本
* @return true|false 确定|取消
* @date 2018-03-29 创建
**/
bool ZYesNoDialog::noIconResult(QString title, QString text)
{
    return result(QMessageBox::NoIcon, title, text);
}
/**
* @brief 弹出问题窗口, 监听用户点击的按钮
* @see result()
* @param[in] title 标题
* @param[in] text 文本
* @return true|false 确定|取消
* @date 2018-03-29 创建
**/
bool ZYesNoDialog::questionResult(QString title, QString text)
{
    return result(QMessageBox::Question, title, text);
}
/**
* @brief 弹出信息窗口, 监听用户点击的按钮
* @see result()
* @param[in] title 标题
* @param[in] text 文本
* @return true|false 确定|取消
* @date 2018-03-29 创建
**/
bool ZYesNoDialog::infoResult(QString title, QString text)
{
    return result(QMessageBox::Information, title, text);
}
/**
* @brief 弹出警告窗口, 监听用户点击的按钮
* @see result()
* @param[in] title 标题
* @param[in] text 文本
* @return true|false 确定|取消
* @date 2018-03-29 创建
**/
bool ZYesNoDialog::warnResult(QString title, QString text)
{
    return result(QMessageBox::Warning, title, text);
}
/**
* @brief 弹出严重错误窗口, 监听用户点击的按钮
* @see result()
* @param[in] title 标题
* @param[in] text 文本
* @return true|false 确定|取消
* @date 2018-03-29 创建
**/
bool ZYesNoDialog::criticalResult(QString title, QString text)
{
    return result(QMessageBox::Critical, title, text);
}
