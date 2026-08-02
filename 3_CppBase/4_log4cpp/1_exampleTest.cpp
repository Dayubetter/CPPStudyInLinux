//
// Created by dayu on 2026/8/2.
//

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

using namespace log4cpp;

int main(int argc, char** argv) {
    // 1.创建目的地对象
    // 2.绑定布局
    // 3.创建记录器
    // 4.记录器设置优先级
    // 5.记录器添加目的地
    // 6.写入日志


    // 基类指针指向派生类对象
    // 设置目的地（输出器）
    // 第一个参数代表目的地名字，仅仅作为指示（随便写
    // 第二个参数是ostream*,此处传入&cout，将目的地设为了输出到终端
    Appender *appender1 = new OstreamAppender("console", &std::cout);
    // 设置布局（将目的地与日至布局进行了绑定）
    // 此处设置为了基本布局，不容易观察
    appender1->setLayout(new BasicLayout());

    // 设置目的地
    // FileApperder的构造函数的第一个参数代表目的地名字（随便写
    // 第二个参数代表保存日志信息的文件名
    Appender *appender2 = new FileAppender("default", "program.log");
    appender2->setLayout(new BasicLayout());



    // 记录器(日志来源
    // getRoot创建root节点的Category
    // 用root这个引用变量进行绑定
    Category& root = Category::getRoot();
    // root节点设置优先级为WARN级别
    // 设置目的地为输出到终端
    root.setPriority(Priority::WARN);
    root.addAppender(appender1);

    // getInstance创建了root节点的Category对象下一级的叶子节点
    // 叶子节点也是Categoty对象
    // 继承了root的优先级和目的地
    // 代码中用sub1引用变量绑定了这个叶子节点Category对象
    Category& sub1 = Category::getInstance(std::string("sub1"));
    // sub1又添加一个目的地 - 保存到文件
    sub1.addAppender(appender2);

    // use of functions for logging messages
    root.error("root error");
    root.info("root info");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

    // printf-style for logging variables
    root.warn("%d + %d == %s ?", 1, 1, "two");

    // use of streams for logging messages
    root << Priority::ERROR << "Streamed root error";
    root << Priority::INFO << "Streamed root info";
    sub1 << Priority::ERROR << "Streamed sub1 error";
    sub1 << Priority::WARN << "Streamed sub1 warn";

    // or this way:
    root.errorStream() << "Another streamed error";

    return 0;
}