#include "reflect.h"
using namespace std;
ReflectFactory* ReflectFactory::instace()
{
    static ReflectFactory m_Instance;
    return &m_Instance;
}
void* ReflectFactory::getObjectByClassName(const string& className)
{
    map<string,pCreateObjectFunc>::iterator itr=m_Map.find(className);
    if(itr != m_Map.end())
        return itr->second();
    else
        return nullptr;
}
void ReflectFactory::registerClass(const string& className, pCreateObjectFunc f)
{
    m_Map.insert(make_pair(className, f));
}
ReflectRegister::ReflectRegister(const std::string& className,ReflectFactory::pCreateObjectFunc func)
{
    ReflectFactory::instace()->registerClass(className, func);
}
