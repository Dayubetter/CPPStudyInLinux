//
// Created by dayu on 2026/10/8.
//
#include <iostream>
using namespace std;

void print(int x) {
    cout << "print:" << x << endl;
}

void display(int x) {
    cout << "display:" << x << endl;
}

void show() {
    cout << "show:" << endl;
}
typedef int INT;
typedef void (*Function)(int);

void test0() {

    // 定义函数指针时要确定其指向的函数的返回类型、参数信息
    void (*p1) (int) = print;
    p1(3);
    p1 = display;
    p1(4);

    // 完整形式
    void (*p2) (int) = &print;
    (*p2)(8);
    p2 = &display;
    (*p2)(9);

    // 可以认为p1  p2 是同一种类型的变量
    // void (*) (int)
    // p2 = &show;

    Function p3 = &print;
    p3(4);
    p3 = &display;
    p3(19);
}

int main() {
    test0();
    return 0;
}