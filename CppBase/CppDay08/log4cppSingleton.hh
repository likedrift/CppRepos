#ifndef __LOG4CPPSINGLETON_HH__
#define __LOG4CPPSINGLETON_HH__
#include <iostream>
#include <string>
#include "log4cpp/Category.hh"
using namespace std;
using namespace log4cpp;
//__LINE__ __func__ __FILE__
#define addPrefix(msg) string("[").append(__FILE__)\
                                .append(":").append(__func__)\
                                .append(":").append(to_string(__LINE__))\
                                .append("]").append(msg).c_str()
#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg))
#define LogNotice(msg) Mylogger::getInstance()->notice(addPrefix(msg))
#define LogInfo(msg) Mylogger::getInstance()->info(addPrefix(msg))
#define LogDebug(msg) Mylogger::getInstance()->debug(addPrefix(msg))


class Mylogger{
public:
    void warn(const char *msg);
    void notice(const char *msg);
    void info(const char *msg);
    void debug(const char *msg);

    static Mylogger * getInstance();
    static void destroy();
private:
    Mylogger();
    ~Mylogger();
private:
    Category & _mycat;
    static Mylogger *_pInstance;
};
//Mylogger *Mylogger::_pInstance = nullptr;

#endif