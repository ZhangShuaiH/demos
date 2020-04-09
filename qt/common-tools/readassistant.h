#ifndef READASSISTANT_H
#define READASSISTANT_H
#include <QDebug>
//#include <QFile>
#include <iostream>
#include <fstream>
/**
* @brief 阅读源码助理
* @note 用于阅读源码使用
* @date 2018-03-15 创建
* @date 2018-03-16 修改: 将函数修改为宏, 代码更加简洁, 可输出更多信息
* @date 2018-03-16 修改: 减少包含的头文件, 给某些变量添加 std:: , 调整行头信息, 将日期时间放到前面
* @version 1.0.1
* @author ZhangShuai
**/

/// 日志文件名称
#define RLOGFILENAME "readLog.log"
/// 行头
#define RLINEHEAD __DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__FUNCTION__<<" "<<__LINE__<<":\t"
/// 输出到 标准输出流
#define RCOUT(X) std::cout<<RLINEHEAD<<(X)<<std::endl;
/// 输出到 debug
#define RDOUT(X) qDebug()<<RLINEHEAD<<(X)<<endl;
//#define RDOUT(X) if(false) // 屏蔽宏 RDOUT(X)
/// 输出到 文件
#define RFOUT(X) std::ofstream RFILE(RLOGFILENAME, std::ofstream::app); RFILE<<RLINEHEAD<<X<<std::endl; RFILE.close();

#endif // READASSISTANT_H
