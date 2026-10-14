//
// Created by dayu on 2026/10/13.
//
#include "Line.h"
#include <iostream>
using namespace std;

class Line::LineImpl {
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
        }

    private:
        int _x;
        int _y;
    };
public:
    LineImpl(int x1, int y1, int x2, int y2)
        :_pt1(x1,y1), _pt2(x2,y2)
    {
        cout<< "LineImpl(int,int,int,int)" << endl;
    }
    ~LineImpl() {
        cout<< "~LineImpl()" << endl;
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

Line::Line(int x1, int y1, int x2, int y2)
    :_pimpl(new LineImpl(x1,y1,x2,y2)) {
    cout<< "Line::Line(int,int,int,int)" << endl;
}

Line::~Line() {
    cout<< "Line::~Line()" << endl;
    if (_pimpl) {
        delete _pimpl;
        _pimpl = nullptr;
    }
}

void Line::printLine() const {
    _pimpl->printLine();
}