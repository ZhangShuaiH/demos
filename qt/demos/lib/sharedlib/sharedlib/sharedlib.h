#ifndef SHAREDLIB_H
#define SHAREDLIB_H

#include "sharedlib_global.h"

class SHAREDLIBSHARED_EXPORT Sharedlib// ������, �ͻ��˿�ֱ�Ӽ���
{

public:
    Sharedlib();
    void test();
};

extern "C" Q_DECL_EXPORT int add(int a, int b);//��������, �ͻ��˿��� QLibrary ����

#endif // SHAREDLIB_H
