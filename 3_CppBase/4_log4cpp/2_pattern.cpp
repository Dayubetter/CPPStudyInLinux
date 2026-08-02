//
// Created by dayu on 2026/8/2.
//
#include <fstream>
#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using namespace std;
using namespace log4cpp;

void func() {
    // 1.创建布局对象
    PatternLayout *layout = new PatternLayout();
    layout->setConversionPattern("%d %c [%p] %m%n"); // 时间 记录器 优先级 日志

    ofstream out("log4cpp.log", ios::app); // 往后追加参数  写入文件可以直接使用FileAppender

    // 2.创建目的地对象
    OstreamAppender *appender = new OstreamAppender("outPut", &cout);
    //OstreamAppender *appender = new OstreamAppender("outPut", &out);
    // 目的地绑定布局
    appender->setLayout(layout); // 目的地与布局一对一绑定！！！
    // 3.创建记录器
    Category &sub1 = Category::getRoot().getInstance("sub1");
    // 4.设置系统优先级
    sub1.setPriority(Priority::DEBUG);
    // 5.记录器添加目的地
    sub1.addAppender(appender);

    // 6.写日志
    sub1.emerg("this is a emerg");
    sub1.fatal("this is a fatal");
    sub1.alert("this is a alert");
    sub1.crit("this is a crit");
    sub1.error("this is a error");
    sub1.warn("this is a warn");
    sub1.notice("this is a notice");
    sub1.info("this is a info");
    sub1.debug("this is a debug");

    // 7.关闭资源
    Category::shutdown();

}

int main(int argc, char *argv[]) {
    func();
}
