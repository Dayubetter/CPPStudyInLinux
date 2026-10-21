//
// Created by dayu on 2026/10/14.
//
#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton* getInstance() {
        // 当多个线程同时进入if语句，会造成Singleton对象被创建多份
        // 但是最终只有一个Singleton对象被_pInstance保存，但只有一个对象被回收，其他都会泄露
        if (nullptr == _pInstance) {
            atexit(&destroy);
            _pInstance = new Singleton(1,2);
        }
        return _pInstance;
    }

    void init(int x, int y) {
        _ix = x;
        _iy = y;
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

    static void destroy() {
        if (_pInstance) {
            // 重点：只在第一次 new 的时候注册一次 atexit，不能写在外面，否则多次注册。
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    int _ix;
    int _iy;
    static Singleton *_pInstance;
};
// Singleton *Singleton::_pInstance = nullptr;  // 饱汉式（懒汉式） 懒加载，等到人为使用Singleton对象的时候才创建

// 俄汉式  即使不使用Singleton对象，也在一开始就创建
Singleton *Singleton::_pInstance = Singleton::getInstance();

void test0() {
    Singleton::getInstance()->init(3,4);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4,5);
    Singleton::getInstance()->print();
    // Singleton::destroy(); // 调用也不会double free
}

int main() {
    test0();
    return 0;
}