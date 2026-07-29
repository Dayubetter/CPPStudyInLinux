//
// Created by dayu on 2026/7/26.
//
#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::endl;


void inputInt(std::istream &is, int & number) {
    cout << "请输入一个整型数据：" << endl;
    is >> number;
    // while (!is.eof()) {
    // 逗号表达式的返回值只取决于最后一个逗号之后的表达式返回
    while (is >> number, !is.eof()) {
        if (is.bad()) {
            cout << "is has broken input" << endl;
            return;
        }else if (is.fail()) {
            cout << " 输入一个整数！" << endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            // is >> number;
        }else {
            cout << "输入成功！" << endl;
            break;
        }
    }
}

void func() {
    int num = 0;
    inputInt(cin,num);
    cout << num << endl;
}

int main(int argc, char *argv[]) {
    func();
    return 0;
}
