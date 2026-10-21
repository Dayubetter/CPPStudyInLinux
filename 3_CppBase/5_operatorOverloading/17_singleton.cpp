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

private:
    int _ix;
    int _iy;
    static Singleton *_pInstance;
};
Singleton *Singleton::_pInstance = nullptr;

void test0() {
    Singleton::getInstance()->init(3,4);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4,5);
    Singleton::getInstance()->print();
    // Singleton::destroy();
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./17_singleton

==6657== Memcheck, a memory error detector
==6657== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6657== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==6657== Command: ./17_singleton
==6657==
Singleton(int,int)
(3, 4)
(4, 5)
==6657==
==6657== HEAP SUMMARY:
==6657==     in use at exit: 8 bytes in 1 blocks
==6657==   total heap usage: 3 allocs, 2 frees, 73,736 bytes allocated
==6657==
==6657== 8 bytes in 1 blocks are still reachable in loss record 1 of 1
==6657==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6657==    by 0x10931F: Singleton::getInstance() (17_singleton.cpp:11)
==6657==    by 0x109235: test0() (17_singleton.cpp:54)
==6657==    by 0x109288: main (17_singleton.cpp:62)
==6657==
==6657== LEAK SUMMARY:
==6657==    definitely lost: 0 bytes in 0 blocks
==6657==    indirectly lost: 0 bytes in 0 blocks
==6657==      possibly lost: 0 bytes in 0 blocks
==6657==    still reachable: 8 bytes in 1 blocks
==6657==         suppressed: 0 bytes in 0 blocks
==6657==
==6657== For lists of detected and suppressed errors, rerun with: -s
==6657== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
int main() {
    test0();
    return 0;
}