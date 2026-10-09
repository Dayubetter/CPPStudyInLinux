//
// Created by dayu on 2026/10/9.
//
#include <iostream>
using namespace std;

class Bar{
public:
    void test0(){ cout << "Bar::test0()" << endl; }
    void test1(int x){ cout << "Bar::test1(): " << x << endl; }
    void test2(){ cout << "Bar::test2(): " << _data << endl; }

    int _data = 10;
};

void test0(){
    Bar * fp = nullptr;
    fp->test0();//ok
    fp->test1(3);//ok
    fp->test2(); //error
}

int main() {
    test0();
    return 0;
}