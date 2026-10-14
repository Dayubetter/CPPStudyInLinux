//
// Created by dayu on 2026/10/13.
//
#include <iostream>
using namespace std;

// Point类只是为了给Line类服务
// 就可以将Point类定义成Line类的内部类
class Line {
public:
    class Point {
    public:
        Point(int x, int y) : _x(x), _y(y) {
            cout<< "Point(int,int)" << endl;
        }
        ~Point() {
            cout<< "~Point()" << endl;
        }

        void print() const{
            cout<< "(" << _x << ", " << _y << ")" << endl;
        }
        // 在内部类中访问外部类的共有成员，可以通过外部类对象直接访问
        void func(const Line &rhs) {
            rhs.printLine();
            rhs._pt1.print();
        }

    private:
        int _x;
        int _y;
    };
public:
    Line(int x1, int y1, int x2, int y2)
        :_pt1(x1,y1), _pt2(x2,y2)
    {
        cout<< "Line(int,int,int,int)" << endl;
    }
    ~Line() {
        cout<< "~Line()" << endl;
    }

    void printLine() const{
        _pt1.print();
        cout <<"--->";
        _pt2.print();
        cout << endl;
    }

private:
    Point _pt1;
    Point _pt2;
};

void test0() {
    Line::Point p1(1,2);

    cout << sizeof(Line) << endl;
    Line ll(1,2,3,4);
    ll.printLine();
}

void test1() {

}

int main(int argc, char *argv[]) {
    test1();
    return 0;
}
