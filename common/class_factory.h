
#pragma once

#include <string>
#include <map>

class BaseClass {
public:
};

typedef BaseClass* (*PTRCreateObject)(void);

class ClassFactory {
private:
    std::map<std::string, PTRCreateObject> m_classMap;
    ClassFactory(){}

public:
    BaseClass* getClassByName(const std::string& className) {
        std::map<std::string, PTRCreateObject>::const_iterator iter;
        iter = m_classMap.find(className);
        if (iter == m_classMap.end())
            return NULL;
        else
            return iter->second();
    }
    void registClass(const std::string& name, PTRCreateObject method) {
        m_classMap.insert(std::pair<std::string, PTRCreateObject>(name, method)) ;  
    }
    static ClassFactory& getInstance() {
        static ClassFactory sLo_factory;  
        return sLo_factory ;  
    }

    class RegisterAction {
    public:
        RegisterAction(const std::string& className,PTRCreateObject ptrCreateFn){
            ClassFactory::getInstance().registClass(className, ptrCreateFn);
        }
    };
};

#define REGISTER(className)                                             \
    BaseClass* objectCreator##className(){                              \
        return new className;                                           \
    }                                                                   \
    ClassFactory::RegisterAction g_creatorRegister##className(          \
        #className, (PTRCreateObject)objectCreator##className)

