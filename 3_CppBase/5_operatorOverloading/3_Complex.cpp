//
// Created by dayu on 2026/8/26.
//
#include <complex>
#include <iostream>
using namespace std;

class Complex {

public:
    Complex(int real, int image)
    : _real(real)
    , _image(image)
    {}

    void print() const {
        cout << _real << " + " << _image << "i" << endl;
    }

    // friend Complex add(const Complex &c1, const Complex &c2);

    friend Complex operator+(const Complex &c1, const Complex &c2);

private:
    int _real;
    int _image;
};

/*
Complex add(const Complex &c1, const Complex &c2) {
    return Complex(c1._real + c2._real, c1._image + c2._image);  // 需要友元
}
*/

Complex operator+(const Complex &c1, const Complex &c2) {
    return Complex(c1._real + c2._real, c1._image + c2._image);
}

void func() {
    Complex c1(2, 3);
    Complex c2(4, 5);
    c1.print();
    c2.print();
    // add(c1, c2).print();
    //本质
    //Complex c3 = operator+(c1, c2);
    Complex c3 = c1 + c2;
    c3.print();
}
int main() {
    func();
    return 0;
}