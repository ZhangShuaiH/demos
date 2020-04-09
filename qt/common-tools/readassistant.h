#ifndef READASSISTANT_H
#define READASSISTANT_H
#include <QDebug>
//#include <QFile>
#include <iostream>
#include <fstream>
/**
* @brief �Ķ�Դ������
* @note �����Ķ�Դ��ʹ��
* @date 2018-03-15 ����
* @date 2018-03-16 �޸�: �������޸�Ϊ��, ������Ӽ��, �����������Ϣ
* @date 2018-03-16 �޸�: ���ٰ�����ͷ�ļ�, ��ĳЩ������� std:: , ������ͷ��Ϣ, ������ʱ��ŵ�ǰ��
* @version 1.0.1
* @author ZhangShuai
**/

/// ��־�ļ�����
#define RLOGFILENAME "readLog.log"
/// ��ͷ
#define RLINEHEAD __DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__FUNCTION__<<" "<<__LINE__<<":\t"
/// ����� ��׼�����
#define RCOUT(X) std::cout<<RLINEHEAD<<(X)<<std::endl;
/// ����� debug
#define RDOUT(X) qDebug()<<RLINEHEAD<<(X)<<endl;
//#define RDOUT(X) if(false) // ���κ� RDOUT(X)
/// ����� �ļ�
#define RFOUT(X) std::ofstream RFILE(RLOGFILENAME, std::ofstream::app); RFILE<<RLINEHEAD<<X<<std::endl; RFILE.close();

#endif // READASSISTANT_H
