#ifndef REFLECT_H
#define REFLECT_H
#include <map>
#include <iostream>
class ReflectFactory
{
public:
    typedef void*(*pCreateObjectFunc)(void);
    static ReflectFactory* instace();
    void* getObjectByClassName(const std::string& className);
    void registerClass(const std::string& className, pCreateObjectFunc f);
private:
    ReflectFactory(){}
    std::map<std::string,pCreateObjectFunc> m_Map;
};
class ReflectRegister
{
public:
    ReflectRegister(const std::string& className,ReflectFactory::pCreateObjectFunc func);
};

#define REFLECT(className) \
void* createObject##className() \
{ \
    return new className(); \
} \
ReflectRegister ReflectRegister##className(#className, createObject##className)


#endif // REFLECT_H
