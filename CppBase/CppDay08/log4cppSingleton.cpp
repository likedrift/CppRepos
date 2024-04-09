#include "log4cppSingleton.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"

Mylogger *Mylogger::_pInstance = nullptr;
Mylogger::Mylogger()
:_mycat(Category::getInstance("mycat"))
{
    //布局器
    auto ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");
    auto ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");
    auto ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");
    //输出器
    auto consolePos = new OstreamAppender("consolePos",&cout);
    consolePos->setLayout(ptn1);
    auto filePos = new FileAppender("fileAppender","log.txt");
    filePos->setLayout(ptn2);
    auto rfPos = new RollingFileAppender("rollingFileAppedner","rf.log",5 * 1024 * 1024,10);
    rfPos->setLayout(ptn3);
    //记录器和过滤器
    _mycat.setPriority(Priority::DEBUG);
    _mycat.addAppender(consolePos);
    _mycat.addAppender(filePos);
    _mycat.addAppender(rfPos);

    cout << "Mylogger()" << endl;
}

Mylogger::~Mylogger(){
    Category::shutdown();
    cout << "~Mylogger()" << endl;
}

Mylogger * Mylogger::getInstance(){
    if(_pInstance == nullptr){
        _pInstance = new Mylogger();
    }
    return _pInstance;
}

void Mylogger::destroy(){
    if(_pInstance){
        delete _pInstance;
        _pInstance = nullptr;
    }
    cout << "Mylogger::destroy()" << endl;
}

void Mylogger::warn(const char *msg){
    _mycat.warn(msg);
}

void Mylogger::notice(const char *msg){
    _mycat.notice(msg);
}

void Mylogger::info(const char *msg){
    _mycat.info(msg);
}

void Mylogger::debug(const char *msg){
    _mycat.debug(msg);
}