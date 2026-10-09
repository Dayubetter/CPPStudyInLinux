#include <iostream>
using std::cout;
using std::endl;

class Point;

class Complex
{
public:
    Complex(int real,int image)
    : _real(real)
    , _image(image)
    {}

    Complex(const Point & rhs);

    void print() const{
        cout << _real << " + "
            << _image << "i"
            << endl;
    }

    /* Complex & operator=(const Point & rhs); */
private:
    int _real;
    int _image;
};

class Point
{
public:
    Point(int x = 0,int y = 1)
    : _ix(x)
    , _iy(y)
    {
        cout << "Point(int,int)" << endl;
    }

    void print(){
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;
    }

    operator int(){
        cout << "operator int函数被调用" << endl;
        return _ix + _iy;
    }

    operator Complex(){
        cout << "operator Complex函数被调用" << endl;
        return Complex(_ix,_iy);
    }

    friend class Complex;
private:
    int _ix;
    int _iy;
};


Complex::Complex(const Point & rhs)
: _real(rhs._ix)
, _image(rhs._iy)
{
    cout << "Complex的特殊的构造函数" << endl;
}

/* Complex & Complex::operator=(const Point & rhs){ */
/*     cout << "Complex的特殊的赋值运算符函数" << endl; */
/*     _real = rhs._ix; */
/*     _image = rhs._iy; */
/*     return *this; */
/* } */


#if 0
void test0(){
    //隐式转换
    //int型变量转换成Point对象
    Point pt = 1;
    pt.print();

    //Point对象转换成int型变量
    //严谨地来说，是由Point对象产生出一个临时的int型变量
    /* int a = pt.operator int(); */
    int a = pt;
    cout << a << endl;
    pt.print();

    //Point对象产生出一个Complex对象
    Complex cx = pt;
    cx.print();
}
#endif

void test1(){
    Point pt(2,7);
    Complex cx(3,9);
    //1.赋值运算符函数 cx.operator=(pt);
    //2.类型转换函数 cx = pt.operator Complex();
    //3.隐式转换（特殊构造函数） cx = Complex(pt);
    cx = pt;
    cx.print();

    //定义了特殊的赋值运算符函数
    //默认的赋值运算符函数仍然存在
    /* Complex cx2(6,7); */
    /* cx2 = cx; */
    /* cx2.print(); */
}

void test2(){
    Point pt(8,9);
    Complex cx = pt;
}

int main(void){
    test2();
    return 0;
}