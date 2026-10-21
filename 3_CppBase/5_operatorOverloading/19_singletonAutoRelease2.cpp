//
// Created by dayu on 2026/10/14.
//
#include <iostream>
using namespace std;

class Singleton {

public:
    class AutoRelease{
    public:
        AutoRelease() {
            cout << "AutoRelease()" << endl;
        }
        ~AutoRelease(){
            cout << "~AutoRelease()" << endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

public:
    static Singleton* getInstance() {
        if (nullptr == _pInstance) {
            _pInstance = new Singleton(1,2);
        }
        return _pInstance;
    }

    void init(int x, int y) {
        _ix = x;
        _iy = y;
    }

    static void destroy() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void print() {
        cout << "(" << _ix << ", " << _iy << ")" << endl;
    }

private:

    Singleton() = default;
    Singleton(int x, int y)
        :_ix(x), _iy(y)
    {
        cout << "Singleton(int,int)" << endl;
    }
    ~Singleton() {
        cout << "~Singleton()" << endl;
    }
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;

    friend class AutoRelease;
private:
    int _ix;
    int _iy;
    static Singleton *_pInstance;
    // 增加一个静态的对象成员
    static AutoRelease _ar; // 存在全局静态区
};
Singleton *Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar; // AutoRelease成员类型   _ar静态成员都加作用域   类定以后立即初始化，静态成员的初始化在所有的对象创建之前


void test0() {
    Singleton::getInstance()->init(3,4);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4,5);
    Singleton::getInstance()->print();
    Singleton::destroy(); // 调用也不会double free
}

int main() {
    test0();
    return 0;
}