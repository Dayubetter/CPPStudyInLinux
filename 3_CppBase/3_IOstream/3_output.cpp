//
// Created by dayu on 2026/7/26.
//
#include <iostream>
#include <unistd.h>
using namespace std;

void func() {
    for (int idx = 0; idx < 1024; ++idx) {
        cout << "a";
    }
    sleep(4); // 等待4秒才会刷新aaaa  如果是1025,就会立马刷新出来
}

void test1(){
    cerr << 1;
    cout << 3;
    sleep(2);
}

int main(int argc, char *argv[]) {
    // func();
    test1();
    return 0;
}
