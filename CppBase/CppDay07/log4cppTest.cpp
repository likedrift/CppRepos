#include <iostream>
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"
using namespace std;
using namespace log4cpp;

void test01(){
    //同时输出到终端、文件和回卷文件
    //一个布局器与一个输出器对象绑定
    PatternLayout * ptn1 = new PatternLayout();
    // %d - 日期格式
    // %c - 记录器名
    // %p - 优先级 枚举
    // %m - 输出信息
    // %n - 当前平台表示文本文件行尾的字符序列 \n
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    // 创建输出器并绑定布局器对象
    OstreamAppender * consolePos = new OstreamAppender("console",&cout);
    consolePos->setLayout(ptn1);
    FileAppender * filePos = new FileAppender("fileAppender","filelog.txt");
    filePos->setLayout(ptn2);
    // 当log文件的大小超过5KB的时候，就新建一个rflog.txt文件，最多有5个历史日志文件
    RollingFileAppender * rfPos = new RollingFileAppender("rollingAppender","rflog.txt",10 * 1024 ,5);
    rfPos->setLayout(ptn3);

    // 创建日志记录器，名称为sub1
    Category & sub1 = Category::getInstance("sub1");
    // 设置优先级
    sub1.setPriority(Priority::INFO);

    // 为记录器设置输出器
    sub1.addAppender(consolePos);
    sub1.addAppender(filePos);
    sub1.addAppender(rfPos);

    int count = 5;
    while(count-- > 0){
        sub1.emerg("emerg message.");
        sub1.fatal("fatal message.");
        sub1.alert("alert message.");
        sub1.crit("crit message.");
        sub1.error("error message.");
        sub1.warn("warn message.");
        sub1.notice("notice message.");
        sub1.info("info message.");
        //sub1.debug("debug message"); 由于优先级是INFO，INFO之下的优先级的文本内容都不会输出
    }

    Category::shutdown();
}

int main(void){
    test01();
    return 0;
}