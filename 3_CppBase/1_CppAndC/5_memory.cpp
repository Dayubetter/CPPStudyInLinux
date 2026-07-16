//
// Created by dayu on 2026/7/16.
//
#include<iostream>
using namespace std;
void func() {
    // 栈区从高地址向低地址，编译器会优化
    int num = 5;
    int num2 = 10;
    cout<<"&num = "<<&num<<endl;
    cout<<"&num2 = "<<&num2<<endl;

    // 堆区从低地址向高地址
    int *ptr = new int(20);
    int *ptr2 = new int(20);
    cout<<"&ptr = "<<&ptr<<endl;
    cout<<"&ptr2 = "<<&ptr2<<endl;
}

int main() {
    func();
}