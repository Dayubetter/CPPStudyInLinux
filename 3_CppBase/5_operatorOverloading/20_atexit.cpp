//
// Created by dayu on 2026/10/21.
//
#include <stdio.h>
#include <iostream>
using namespace std;
void display() {
    cout << "display()" << endl;
}

void print() {
    cout << "print()" << endl;
}

void test0() {
    // 同一个函数注册几次，调用几次
    // 先注册的函数会后调用
    atexit(&display);
    atexit(&display);
    atexit(&print);
}
int main() {
    test0();
    cout << "over" << endl;
    return 0;
}
