//
// Created by dayu on 2026/8/26.
//
#include <iostream>
#include <limits>
using namespace std;

void inputInt(istream & is, int & num) {
    cout << "请输入一个int型整数数据" << endl;
    while (is >> num , !is.eof()) {
        if (is.bad()) {
            cout << "istream has broken!" << endl;
            return;
        }else if (is.fail()) {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "看清楚，输入int型" << endl;
        }else {
            break;
        }
    }
}

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

    // 重载 <<
    // 这样重载的效果只能实现cx1 << cout
    // 与内置类型的使用不一致
    /*ostream & operator<<(ostream &os) {
        os << _real << " + " << _image << "i";
        return os;
    }*/

    friend
    ostream &operator<<(ostream &lhs, const Complex &rhs);

    friend
    istream &operator>>(istream &lhs, Complex &rhs);
private:
    int _real;
    int _image;
};

ostream & operator<<( ostream & lhs, const Complex & rhs) {
    lhs << rhs._real << " + " << rhs._image << "i" << endl;
    return lhs;
}

istream & operator>>( istream & lhs, Complex & rhs) {
    cout << "请输入实部： " << endl;
    // lhs >> rhs._real;
    inputInt(lhs,rhs._real);
    cout << "请输入虚部： " << endl;
    // lhs >> rhs._image;
    inputInt(lhs,rhs._image);

    // 链式输入无法处理错误输入的情况
    // lhs >> rhs._real >> rhs._image;
    return lhs;
}

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


void func2() {
    Complex cx1(1, 2);
    //cx1.print();

    //cx1.operator<<(cout);
    //cx1 << cout << endl;

    // 相当于普通函数，输出流运算符作为第一个参数，
    operator<<(cout, cx1) << endl;
    cout << cx1 << endl;

    // operator>>(cin, cx1);
    cin >> cx1;
    cout << cx1 << endl;
}
int main() {
    //func();
    func2();
    return 0;
}