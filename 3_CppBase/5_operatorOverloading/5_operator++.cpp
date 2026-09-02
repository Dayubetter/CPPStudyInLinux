//
// Created by dayu on 2026/9/2.
//
#include <complex>
#include <iostream>
using namespace std;

class Complex {
public:
    Complex(int real, int image)
    :_real(real), _image(image)
    {}

    void print() const {
        cout << _real << " + " << _image << "i" << endl;
    }

    Complex & operator+=(const Complex & rhs) {
        _real += rhs._real;
        _image += rhs._image;
        return *this;
    }

    friend Complex operator+(const Complex &c1, const Complex &c2);

    Complex & operator++() {
        cout << "前置++函数" << endl;
        ++_real;
        ++_image;
        return *this;
    }

    // 后置++的重载函数的参数列表需要加一个int 与前置++作区分
    Complex operator++(int) {
        cout << "后置++" << endl;
        Complex temp(*this);
        ++_real;
        ++_image;
        return temp;
    }

private:
    int _real;
    int _image;
};

Complex operator+(const Complex &c1, const Complex &c2) {
    return Complex(c1._real + c2._real, c1._image + c2._image);
}

void func() {
    int a = 1,b = 2;
    cout << &a << endl;
    cout <<&(a += b) << endl;
    cout << a << endl;
    cout << b << endl;

    Complex cx1(1,2);
    cout << &cx1 << endl;
    // cx1.operator++();
    cout << &(++cx1) << endl;
    cx1.print();

    // cx1.operator++(1);
    (cx1++).print();
    cx1.print();
}
int main() {
    func();
    return 0;
}