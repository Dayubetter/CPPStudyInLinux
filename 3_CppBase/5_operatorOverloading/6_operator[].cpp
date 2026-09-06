//
// Created by dayu on 2026/9/6.
//
#include <cstring>
#include <iostream>
using namespace std;

class CharArray {
public:
    CharArray(const char* pstr)
    :_capacity(strlen(pstr) + 1)
    ,_data(new char[_capacity] ()) {
        strcpy(_data,pstr);
    }
    ~CharArray() {
        if (_data) {
            delete[] _data;
            _data = nullptr;
        }
    }

    char & operator[](size_t idx) {
        if (idx < _capacity - 1) {
            return _data[idx];
        }else {
            cout << "out of range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }

    // 前一个const的意义是返回值是一个const引用，不能用返回值进行写操作
    // 后一个const的意义是将这个函数设置为const成员函数
    // （1）const对象可以使用这个函数
    // （2）在函数体中不能修改对象的数据成员
    const char & operator[](size_t idx) const{
        if (idx < _capacity - 1) {
            return _data[idx];
        }else {
            cout << "out of range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }

private:
    size_t _capacity;
    char * _data;
};

void func() {
    char arr[] = "hello";
    cout << arr[0] << endl;

    CharArray ca("hello");
    ca.operator[](0);
    cout << ca[0] << endl;
    ca[0] = 'H';
    cout << ca[0] << endl;

    const CharArray ca2("world");
    cout << ca2[0] << endl;
    // ca2[0] = 'W';  // const char & 限制利用返回值进行写操作
    cout << ca2[0] << endl;
}

int main() {
    func();
}