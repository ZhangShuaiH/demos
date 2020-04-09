#include "calculator.h"

Calculator::Calculator()
{

}
/**
* @brief 计算两大实数的积
* @note  非实数的积为空
* @version 1.0
* @date 2018-08-22 创建
* @author ZhangShuai
**/
QString Calculator::bigRealNumberMultiply(QString a, QString b){
    QString res = "";
    QChar symbol;
    int point_num = 0;
    /// 验证实数
    QRegExp re("^[+-]?\\d+(\\.\\d+)?$");
    if(!re.exactMatch(a) || !re.exactMatch(b)){
        return res;
    }
    /// 去除符号
    QChar  a_symbol = getSymbol(a);
    QChar  b_symbol = getSymbol(b);
    symbol = a_symbol==b_symbol?'+':'-';

    /// 去除小数点
    int a_point_num = a.indexOf('.') == -1 ? 0:a.size()-1-a.indexOf('.');// 小数的位数
    a.replace('.', "");// 去除小数点
    int b_point_num = b.indexOf('.') == -1 ? 0:b.size()-1-b.indexOf('.');// 小数的位数
    b.replace('.', "");// 去除小数点
    point_num = a_point_num+b_point_num;

    res = "0";
    /// 逐位计算
    for(int i = a.size()-1; i >= 0; i--){
        int carry = 0;// 进位
        QString resTemp;
        for(int j = b.size()-1; j >= 0; j--){
            int temp;
            temp = QString(a.at(i)).toInt()*QString(b.at(j)).toInt()+carry;
            resTemp = QString::number(temp%10)+resTemp;
            carry = temp/10;
        }
        if(carry>0){
            resTemp = QString::number(carry)+resTemp;
        }
        for(int m = 0; m < a.size()-1-i; m++){
            resTemp += "0";
        }
        res = bigRealNumberAdd(res, resTemp);
    }
    /// 添加小数点
    if(point_num>0){
        if(res.size()-point_num > 0){
            res.insert(res.size()-point_num, '.');
        }else {
            int n = point_num-res.size();
            for(int i = 0; i <= n; i++){
                res.insert(0, '0');
            }
            res.insert(1, '.');
        }
    }
    /// 添加符号位
    if(symbol == '-'){
        res.insert(0, symbol);
    }

    return res;
}
/**
* @brief 计算两大实数的和
* @note  非实数的和为空
* @version 1.0
* @date 2018-08-22 创建
* @author ZhangShuai
**/
QString Calculator::bigRealNumberAdd(QString a, QString b){
    QString res = "";
    QChar symbol;
    /// 验证实数
    QRegExp re("^[+-]?\\d+(\\.\\d+)?$");
    if(!re.exactMatch(a) || !re.exactMatch(b)){
        return res;
    }
    /// 去除符号
    QChar  a_symbol = getSymbol(a);
    QChar  b_symbol = getSymbol(b);
    appendPoint(a);
    appendPoint(b);
    /// 对齐位数
    align(a,b);
    /// 逐位计算
    if(a_symbol == b_symbol){// 符号位相等
        int carry = 0;// 进位
        int plus = 0;// 加和
        for(int i = a.size()-1; i >= 0; i--){
            if(a.at(i) != '.'){
                plus = QString(a.at(i)).toInt()+QString(b.at(i)).toInt()+carry;
                res = QString::number(plus%10)+res;
                carry = plus/10;
            }else {
                res = "." + res;
            }
        }
        if(carry>0){
            res = QString::number(carry)+res;
        }
        symbol = a_symbol;
    }else {// 符号位不相等
        int borrow = 0;// 借位
        int gap = 0;// 差
        switch (compare(a,b)) {
        case 1:
            for(int i = a.size()-1; i >= 0; i--){
                if(a.at(i) != '.'){
                    gap = QString(a.at(i)).toInt()-QString(b.at(i)).toInt()-borrow;
                    if(gap<0){
                        gap += 10;
                        borrow = 1;
                    }else {
                        borrow = 0;
                    }
                    res = QString::number(gap)+res;
                }else {
                    res = "." + res;
                }
            }
            symbol = a_symbol;
            break;
        case 0:
            return "0";
            break;
        case -1:
            for(int i = a.size()-1; i >= 0; i--){
                if(a.at(i) != '.'){
                    gap = QString(b.at(i)).toInt() - QString(a.at(i)).toInt()-borrow;
                    if(gap<0){
                        gap += 10;
                        borrow = 1;
                    }else {
                        borrow=0;
                    }
                    res = QString::number(gap)+res;
                }else {
                    res = "." + res;
                }
            }
            symbol = b_symbol;
            break;
        default:
            break;
        }
    }
    /// 去除多余的零
    QString tempRes;
    int i,j;
    for(i = 0; i<res.size() && res.at(i) == '0' && res.at(i) != '.'; i++);
    for(j = res.size()-1; i>=0 && res.at(j) == '0' && res.at(j) != '.'; j--);
    for(int m = i; m <= j; m++){
        tempRes.append(res.at(m));
    }
    if(tempRes.at(0) == '.'){
        tempRes.insert(0, '0');
    }
    if(tempRes.at(tempRes.size()-1) == '.'){
        tempRes.remove(tempRes.size()-1, 1);
    }
    res = tempRes;
    /// 添加符号位
    if(symbol == '-'){
        res.insert(0, '-');
    }
    return res;
}

void Calculator::test()
{
    test_multiply1();
}
/// 抽取并去除符号位
QChar Calculator::getSymbol(QString &readNumber){
    QChar symbol;
    if(readNumber.at(0)=='+' || readNumber.at(0)=='-'){
        symbol = readNumber.at(0);
        readNumber.remove(0,1);
    }else {
        symbol = '+';
    }
    return symbol;
}
/// 如果是整数，则在末尾添加小数点
void Calculator::appendPoint(QString &readNumber){
    if(readNumber.indexOf('.') == -1){
        readNumber.append('.');
    }
}
/// 数字对齐，较短的补零
void Calculator::align(QString &a, QString &b){
    int a_dec_size = a.size()-1-a.indexOf('.');// 小数部分的位数
    int b_dec_size = b.size()-1-b.indexOf('.');// 小数部分的位数
    /// 对齐小数部分
    if(a_dec_size>b_dec_size){
        for(int i = 0; i < a_dec_size-b_dec_size; i++){
            b.append('0');
        }
    }else {
        for(int i = 0; i < b_dec_size-a_dec_size; i++){
            a.append('0');
        }
    }
    int a_int_size = a.indexOf(QRegExp("\\.")) - a.indexOf(QRegExp("\\d"));// 整数部分的位数
    int b_int_size = b.indexOf(QRegExp("\\.")) - b.indexOf(QRegExp("\\d"));// 整数部分的位数
    /// 对齐整数部分
    if(a_int_size>b_int_size){
        for(int i = 0; i < a_int_size-b_int_size; i++){
            b.insert(0,'0');
        }
    }else {
        for(int i = 0; i < b_int_size-a_int_size; i++){
            a.insert(0,'0');
        }
    }
}

int Calculator::compare(const QString &a, const QString &b){
    if(a.size() != b.size()){
        return -2;//错误
    }else {
        for(int i = 0; i < a.size(); i++){
            if(QString(a.at(i)).toInt()>QString(b.at(i)).toInt()){
                return 1;// a 大
            }else if(QString(a.at(i)).toInt()<QString(b.at(i)).toInt()){
                return -1;// a 小
            }
        }
        return 0;// 相等
    }
}

void Calculator::test_addRealNumber0(){
    // 【整数】【小数】【正数】【负数】->【正整数】【负整数】【正小数】【负小数】
    // 【正整数 正整数】【正整数 负整数】【正整数 正小数】【正整数 负小数】
    myDebug((bigRealNumberAdd("123", "123") == "246"));
    myDebug((bigRealNumberAdd("123", "-124") == "-1"));
    myDebug((bigRealNumberAdd("123", "1.123") == "124.123"));
    myDebug((bigRealNumberAdd("123", "-1.123") == "121.877"));
    // 【负整数 负整数】【负整数 正小数】【负整数 负小数】
    myDebug((bigRealNumberAdd("-123", "-123") == "-246"));
    myDebug((bigRealNumberAdd("-123", "123.123") == "0.123"));
    myDebug((bigRealNumberAdd("-123", "-0.123") == "-123.123"));
    // 【正小数 正小数】【正小数 负小数】
    myDebug((bigRealNumberAdd("123.123", "123.123") == "246.246"));
    myDebug((bigRealNumberAdd("123.123", "-123.123") == "0"));

    // 【负小数 负小数】
    myDebug((bigRealNumberAdd("-123.123", "-123.123") == "-246.246"));
}

void Calculator::test_addRealNumber1(){
    double aa[] = {-242.93, -31.66, -836.99, -800.47, -39.945, -251.51, -942.3, 929.72, 249.5, 75.2, 964.72, 245.3, 212.2, 27.72, -525.71, 866.14, 290.32, -189.37, 838.55, -450.1};
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            bool res = bigRealNumberAdd(QString::number(aa[i]), QString::number(aa[j])) == QString::number((aa[i]+aa[j]));
            myDebug(res);
            if(!res){
                myDebug(aa[i]);
                myDebug(aa[j]);
                myDebug(aa[i]+aa[j]);
                myDebug(bigRealNumberAdd(QString::number(aa[i]), QString::number(aa[j])));
                myDebug("");
            }
        }
    }
}

void Calculator::test_multiply0(){
    // 【整数】【小数】【正数】【负数】->【正整数】【负整数】【正小数】【负小数】
    // 【正整数 正整数】【正整数 负整数】【正整数 正小数】【正整数 负小数】
    myDebug((bigRealNumberMultiply("123", "123") == "15129"));
    myDebug((bigRealNumberMultiply("123", "-124") == "-15252"));
    myDebug((bigRealNumberMultiply("123", "1.123") == "138.129"));
    myDebug((bigRealNumberMultiply("123", "-1.123") == "-138.129"));
    // 【负整数 负整数】【负整数 正小数】【负整数 负小数】
    myDebug((bigRealNumberMultiply("-123", "-123") == "15129"));
    myDebug((bigRealNumberMultiply("-123", "123.123") == "-15144.129"));
    myDebug((bigRealNumberMultiply("-123", "-0.123") == "15.129"));
    // 【正小数 正小数】【正小数 负小数】
    myDebug((bigRealNumberMultiply("123.123", "123.123") == "15159.273129"));
    myDebug((bigRealNumberMultiply("123.123", "-123.123") == "-15159.273129"));

    // 【负小数 负小数】
    myDebug((bigRealNumberMultiply("-123.123", "-123.123") == "15159.273129"));
    // 其它
    myDebug((bigRealNumberMultiply("0.678", "0.08678") == "0.05883684"));
}

void Calculator::test_multiply1()
{
    double aa[] = {-242.93, -31.66, -836.99, -800.47, -39.945, -251.51, -942.3, 929.72, 249.5, 75.2, 964.72, 245.3, 212.2, 27.72, -525.71, 866.14, 290.32, -189.37, 838.55, -450.1};
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            bool res = bigRealNumberMultiply(QString::number(aa[i]), QString::number(aa[j])) == QString::number((aa[i]*aa[j]));
            myDebug(res);
            if(!res){
                myDebug(aa[i]);
                myDebug(aa[j]);
                myDebug(aa[i]*aa[j]);
                myDebug(bigRealNumberMultiply(QString::number(aa[i]), QString::number(aa[j])));
                myDebug("");
            }
        }
    }
}

void Calculator::test_compare(){
    myDebug((compare("123", "123") == 0));
    myDebug((compare("123", "124") == -1));
    myDebug((compare("125", "124") == 1));
    myDebug((compare("1251", "124") == -2));
}
