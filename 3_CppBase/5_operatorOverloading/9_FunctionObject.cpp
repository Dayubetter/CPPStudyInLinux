//
// Created by dayu on 2026/9/24.
//
#include <iostream>
using namespace std;

class FunctionObject {
public:
    void operator()() {
        cout << "Hello World" << endl;
    }
    int operator()(int x,int y) {
        return x+y;
    }

    double operator()(double x) {
        return x*x;
    }
};

void test0() {
    FunctionObject fo;
    // 函数调用运算符：函数的返回值是根据设计灵活设置的
    // fo.operator()();
    fo(); // 让对象像一个函数一样被调用

    cout << fo(1,2) << endl;

    cout << fo(3.4) << endl;
}

int main(void) {
    test0();
    return 0;
}