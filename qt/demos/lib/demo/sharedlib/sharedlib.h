#ifndef SHAREDLIB_H
#define SHAREDLIB_H

#include "sharedlib_global.h"
#include "myclass.h"

class SHAREDLIBSHARED_EXPORT Sharedlib
{

public:
    Sharedlib();
};
extern "C" Q_DECL_EXPORT MyClass *getMyClass();

#endif // SHAREDLIB_H
