//
// Created by dayu on 2026/7/14.
//
#include <iostream>
using namespace std;

namespace dy {
    int num = 10;

    void func() {
        cout << num << endl;
    }

    namespace cpp {
        int num = 20;
        void func() {
            cout << num << endl;
        }
    } // end of namespace cpp
} // end of namespace dy


namespace {
    int num = 100;
    void func() {
        cout << num << endl;
    }
} // end of anonymous namespace

void test() {
    ::func();
}

int main() {
    cout << "Hello world!" << endl;
    dy::func();
    dy::cpp::func();
    test();
}