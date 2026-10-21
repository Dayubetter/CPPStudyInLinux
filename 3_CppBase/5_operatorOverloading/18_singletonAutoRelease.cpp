//
// Created by dayu on 2026/10/14.
//
#include <iostream>
using namespace std;

class Singleton {
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
};
Singleton *Singleton::_pInstance = nullptr;

class AutoRelease {
public:
    AutoRelease(Singleton *p)
        :_p(p)
    {}
    ~AutoRelease() {
        if (_p) {
            delete _p;
            _p = nullptr;
        }
    }
private:
    Singleton *_p;
};

void test0() {
    Singleton::getInstance()->init(3,4);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4,5);
    Singleton::getInstance()->print();
    Singleton::destroy();
}

void test1() {
    Singleton *p = Singleton::getInstance();
    p->print();
    // delete p;
}

void test2() {
    AutoRelease ar(Singleton::getInstance());
    AutoRelease ar2(Singleton::getInstance()); // double free
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4,5);
    Singleton::getInstance()->print();
    // Singleton::destroy();  // double free
}

int main() {
    test2();
    return 0;
}