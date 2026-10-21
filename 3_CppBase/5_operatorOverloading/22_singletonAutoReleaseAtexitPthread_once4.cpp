//
// Created by dayu on 2026/10/14.
//
#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton* getInstance() {
        pthread_once(&_once,init_r); // 创建对象的功能交给init_r函数，pthread_once控制init_r，只会执行一次
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

private:

    static void init_r() {
        _pInstance = new Singleton(1,2);
        atexit(&destroy); // init_r不能被手动调用，否则会造成内存泄露--绕开了getInstance中通过pthread_once进行的控制
    }


    static void destroy() {
        if (_pInstance) {
            // 重点：只在第一次 new 的时候注册一次 atexit，不能写在外面，否则多次注册。
            delete _pInstance;
            _pInstance = nullptr;
        } // destroy不能手动调用，否则再回收对象后再想通过getInstance创建对象会失败-- init_r只执行一次
    }

private:
    int _ix;
    int _iy;
    static Singleton *_pInstance;
    static pthread_once_t _once;
};
Singleton *Singleton::_pInstance = nullptr;  // 饱汉式（懒汉式） 懒加载，等到人为使用Singleton对象的时候才创建
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

// 俄汉式  即使不使用Singleton对象，也在一开始就创建
//Singleton *Singleton::_pInstance = Singleton::getInstance();

void test0() {
    Singleton::getInstance()->init(3,4);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4,5);
    Singleton::getInstance()->print();
    // Singleton::destroy();
}

int main() {
    test0();
    return 0;
}