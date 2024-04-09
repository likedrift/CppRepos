#include <iostream>
#include <string>
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"

using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

/**
 * 需要一个Category
 * 
 * auto无法推导出引用类型，但是能够推导指针类型
 * 
 * 布局和输出器必须1对1
 * 
 * 如果把静态成员的类外定义放在头文件中 会multidefine
 * 
 * inline在编译时期起作用进行替换 而宏函数在预处理时期起作用
 * 使用宏函数
*/

class Mylogger
{
public:
    inline void appendMsg(const char *msg){
        _msg = msg;
        _msg += " File:";
        _msg.append(__FILE__);
        _msg += ",Function:";
        _msg.append(__func__);
        _msg += ",Line:";
        _msg.append(std::to_string(__LINE__));
    }

	void warn(const char *msg){
        appendMsg(msg);
        _sub.warn(_msg);
    }
	void error(const char *msg){
        appendMsg(msg);
        _sub.error(_msg);
    }
	void debug(const char *msg){
        appendMsg(msg);
        _sub.debug(_msg);
    }
	void info(const char *msg){
        appendMsg(msg);
        _sub.info(_msg);
    }
    void fatal(const char *msg){
        appendMsg(msg);
        _sub.fatal(_msg);
    }
    void crit(const char *msg){
        appendMsg(msg);
        _sub.crit(_msg);
    }
	
    static Mylogger * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }

private:
// Mylogger(PatternLayout *ptn,OstreamAppender * consolePos,Category sub)
	Mylogger()
    :_ptn(new PatternLayout())
    ,_consolePos(new OstreamAppender("console",&cout))
    ,_sub(Category::getInstance("_sub"))
    ,_msg("")
    
    {
        _ptn->setConversionPattern("%d %c [%p] %m%n");
        _consolePos->setLayout(_ptn);
        _sub.addAppender(_consolePos); // 输出器绑定布局器对象
    }
	~Mylogger(){
        // if(_ptn || _consolePos){
        //     delete _ptn;
        //     delete _consolePos;
        //     _ptn = nullptr;
        //     _consolePos = nullptr;
        // }
        Category::shutdown();
    }
    
private:
    PatternLayout * _ptn;
    OstreamAppender * _consolePos;
    Category & _sub;
    static Mylogger * _pInstance;
    string _msg;
};
Mylogger *Mylogger::_pInstance = nullptr;

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger * log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    // LogInfo("The log is info message");
    // LogError("The log is error message");
    // LogWarn("The log is warn message");
    // LogDebug("The log is debug message");
}


int main(void){
    test0();
    //test1();
    return 0;
}