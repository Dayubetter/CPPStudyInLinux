//
// Created by dayu on 2026/7/17.
//
#include <cstring>
#include <iostream>
using namespace std;
void func() {
    char arr[6] = {'h', 'e', 'l', 'l', 'o'};
    char arr2[] = {'w', 'o', 'r', 'l', 'd'}; // 不安全 没有终止符
    char arr3[] = "hello";

    cout << arr << endl;
    cout << arr2 << endl; // 输出worldhello
    cout << arr3 << endl;

    printf("%p\n", arr);
    printf("%p\n", arr2);
    printf("%p\n", arr3);

    const char *cstr = "hello";
    cout << sizeof(cstr) << endl; // 获取指针大小 8字节
    cout << strlen(cstr) << endl;
}

void func2(int *x,int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}
int main() {
    func();
    int x = 10, y = 20;
    func2(&x,&y);
    cout << x << y <<endl;
}