#ifndef SHAREDLIB_H
#define SHAREDLIB_H

#include "sharedlib_global.h"

class SHAREDLIBSHARED_EXPORT Sharedlib// 导出类, 客户端可直接加载
{

public:
    Sharedlib();
    void test();
};

extern "C" Q_DECL_EXPORT int add(int a, int b);//导出函数, 客户端可用 QLibrary 加载

#endif // SHAREDLIB_H
