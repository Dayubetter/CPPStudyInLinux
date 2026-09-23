//
// Created by dayu on 2026/9/20.
//
#include <iostream>
using namespace std;

class Data
{
public:
    Data() {
        cout << "Data()" << endl;
    }
    ~Data() {
        cout << "~Data()" << endl;
    }

    int getData() const{ return _data; }
private:
    int _data = 10;
};

class MiddleLayer {
public:
    MiddleLayer(Data * p) : _pdata(p) {
        cout << "MiddleLayer(Data*)" << endl;
    }
    ~MiddleLayer() {
        cout << "~MiddleLayer()" << endl;
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }

    Data* operator->() {
        return _pdata;
    }

    Data& operator*() { return *_pdata; }

    friend class ThirdLayer; // 一步到位解引用
private:
    Data * _pdata;
};

class ThirdLayer {
public:
    ThirdLayer(MiddleLayer * pml)
        : _pml(pml) {
        cout << "ThirdLayer(MiddleLayer*)" << endl;
    }
    ~ThirdLayer() {
        cout << "~ThirdLayer()" << endl;
        if (_pml) {
            delete _pml;
            _pml = nullptr;
        }
    }

    MiddleLayer& operator->() {
        return  *_pml;
    }

    // 一步一步解引用
    // MiddleLayer& operator*() {
    //     return  *_pml;
    // }
    // 一步到位解引用
    Data& operator*() {
        // return *(*_pml);
        // return  (*_pml).operator*();
        return *((*_pml)._pdata); // 需要有元，ThirdLayer作为MiddleLayer的有元，访问MiddleLayer的私有成员
        }

private:
    MiddleLayer * _pml;
};

void test0() {
    // 原生指针的用法
    Data * pd = new Data();
    cout << pd->getData() << endl;
    cout << (*pd).getData() << endl;
    // delete pd;

    MiddleLayer ml(pd);
    // delete pd;  //double free
}

void test1() {

    Data * pd = new Data();
    cout << pd->getData() << endl;
    cout << (*pd).getData() << endl;
    delete pd;

    // 更推荐这样使用MiddleLayer对象
    MiddleLayer ml(new Data());
    // 编译器会自动加上一个->
    // 第一个->和operator连在一起作为函数名
    // 第二个->就是原生的箭头运算符用法
    cout << ml.operator->() ->getData() << endl;
    cout << ml->getData() << endl;

    cout << ml.operator*() .getData() << endl;
    cout << (*ml).getData() << endl;

    // MiddleLayer对象已经和Data*类型的原生指针拥有类似功能
    // 能够管理Data对象，还能访问Data对象的成员
    // MiddleLayer对象还能自动释放其管理的Data对象的空间
    // 利用对象的声明周期回收资源

    // ThirdLayer tl(&ml); // error
}

void test2() {
    MiddleLayer * pml = new MiddleLayer(new Data());
    ThirdLayer tl(pml);
    // delete pml; // double free
}

void test3() {
    ThirdLayer tl(new MiddleLayer(new Data()));
    // 第一个operator->函数是ThirdLayer的成员函数
    // 第二个operator->函数是MiddleLayer的成员函数
    // 最后一个->是编译器加上，原生箭头运算符的用法
    cout << tl.operator->().operator->() ->getData() << endl;
    // ThirdLayer对象的operator->函数只需要返回MiddleLayer对象
    // 因为MiddleLayer类中已经重载了箭头运算符作为铺垫
    // 所以MiddleLayer对象可以直接用->访问Data类的成员
    cout << tl.operator->() ->getData() << endl;
    cout << tl->getData() << endl;

    // 一步一步解引用
    // cout << tl.operator*().operator*().getData() << endl;
    // cout << (*(*tl)).getData() << endl;

    // 一步到位解引用
    cout << tl.operator*().getData() << endl;
    cout << (*tl).getData() << endl;
}

int main() {
    // test0();
    // test1();
    test3();
    return 0;
}