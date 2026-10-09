//
// Created by dayu on 2026/10/8.
//
#include <iostream>
using namespace std;

void print(int x) {
    cout << "print:" << x << endl;
}

void display(int x) {
    cout << "display:" << x << endl;
}

class FFF
{
public:
    void print(int x){
        cout << "FFF::print:" << x << endl;
    }

    void display(int x){
        cout << "FFF::display:" << x << endl;
    }

    static void show(int x) {
        cout << "FFF::show:" << x << endl;
    }
};

class DDD {
    public:
    void print(int x){
        cout << "DDD::print:" << x << endl;
    }
};

typedef void (*Function)(int);
typedef void (FFF::*MemberFunction)(int);
void test0() {
    Function p1;
    p1 = FFF::show;
    p1(4);

    // Function p2 = FFF::print; // error
    // void (FFF::*p3)(int) = &DDD::print; // error

    // 成员函数指针定义时要确定其指向的成员函数的类、返回类型、参数信息
    void (FFF::*p2)(int) = &FFF::print;
    MemberFunction p3;
    p3 = &FFF::print;
    FFF fff;
    // .*成员指针运算符的形式之一
    (fff.*p3)(4);

    FFF* fp = new FFF();
    fp->print(2);

    // ->*成员指针运算符的形式之二
    (fp->*p3)(33);

    // 关于空指针的使用，作为了解
    delete fp;
    fp = nullptr;

    fp->print(555);
    (fp->*p3)(444); // 还可以调用
}

void test1() {

    void (*p1) (int) = print;
    p1(3);
    p1 = display;
    p1(4);

    Function p3 = &print;
    p3(4);
    p3 = &display;
    p3(19);
}

int main() {
    test0();
    return 0;
}