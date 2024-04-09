#include "log4cppSingleton.hh"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test01(){
    cout << addPrefix("test01") << endl;
    Mylogger::getInstance()->warn("warn msg");
    Mylogger::getInstance()->notice("notice msg");
    Mylogger::getInstance()->info("info msg");
    Mylogger::getInstance()->debug("debug msg");
    Mylogger::destroy();
}

void test02(){
    LogWarn("LogWarn");
    LogNotice("LogNotice");
    LogInfo("LogInfo");
    LogDebug("LogDebug");
    Mylogger::destroy();
}

int main(void){
    test01();
    test02();
    return 0;
}