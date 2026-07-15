//
// Created by dayu on 2026/7/15.
//
#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }

// 函数指针
void func() {
    // 省略写法
    int (*p) (int ,int) = add;
    cout << p(10, 2) << endl;
    // 完整写法
    int (*p2) (int ,int) = &add;
    cout << (*p2)(10, 10) << endl;
}

// 指针函数
int num = 10;
int * func1() {
    int *p = &num;
    return p;
}
int main() {
    func();
    cout << func1() << endl; // 地址
    cout << *func1() << endl; // 解引用10
}