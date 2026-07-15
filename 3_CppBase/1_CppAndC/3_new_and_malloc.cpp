//
// Created by dayu on 2026/7/15.
//
#include <cstring>
#include <iostream>
using namespace std;

void func1() {
    // 总泄露12字节
    int *p = (int*) malloc(sizeof(int));
    *p = 10;
    cout << *p << endl;

    int *p1 = new int(4);
    cout << *p1 << endl;

    int *p2 = new int();
    cout << *p2 << endl;
}

void func2() {
    // 申请数组空间  泄露40字节 初始化默认都是0
    int *p3 = new int[10]();
    for (int i = 0; i < 10; ++i) {
        p3[i] = i;
    }
    for (int i = 0; i < 10; ++i) {
        cout << p3[i] << endl;
    }
}

void func3() {
    int *p4 = new int[10]{0,1, 2, 3, 4, 5, 6, 7, 8, 9};
    // p4是一个指针变量，不是数组本身，64位系统下指针占8字节 sizeof(p4)=8
    for (int i = 0; i < 10; ++i) {
        cout << p4[i] << endl;
    }
}

void func4() {
    char *p5 = new char[6]{'h', 'e', 'l', 'l', 'o', '\0'};
    cout << p5 << endl;
    cout << strlen(p5) << endl;
    const char *p6 = "hello";
    cout << p6 << endl;
    cout << strlen(p6) << endl;
}
int main () {
    //func1();
    //func2();
    //func3();
    func4();
}