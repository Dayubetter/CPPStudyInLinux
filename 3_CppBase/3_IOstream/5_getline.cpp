//
// Created by dayu on 2026/7/28.
//
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

// 基类引用绑定派生类对象
void checkStatus(const istream& is) {
    cout << "is's goodbit:" << is.good() << endl;
    cout << "is's badbit:" << is.bad() << endl;
    cout << "is's eofbit:" << is.eof() << endl;
    cout << "is's failbit:" << is.fail() << endl;
}

void func() {
    ifstream ifs;
    ifs.open("3_output.cpp");
    checkStatus(ifs);

    // 方式一：兼容C
    /*char buffer[100] = {0};
    while (ifs.getline(buffer, sizeof(buffer))) {
        cout << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }*/
    // 方式二：利用string中函数
    string line;
    while (getline(ifs, line)) {
        cout << line << endl;

    }
    ifs.close();
}

int main() {
    func();
}