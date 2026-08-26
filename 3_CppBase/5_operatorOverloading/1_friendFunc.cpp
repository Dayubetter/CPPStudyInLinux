//
// Created by dayu on 2026/8/4.
//
#include <math.h>
#include <iostream>
using namespace std;

class Point {
public:
    Point(int x, int y)
    : _ix(x)
    , _iy(y)
    {}

    // 将一个普通函数声明为Point类的有元函数
    // 那么这个有元函数中可以通过Point对象访问Point类私有的成员
    friend
    double distance(const Point &p1,const Point &p2);
private:
    int _ix;
    int _iy;
};

double distance(const Point& p1,const Point& p2) {
    return sqrt(pow(p1._ix - p2._ix,2) + pow(p1._iy - p2._iy,2));
}

void func() {
    Point pt1(0,0);
    Point pt2(3,4);
    cout << distance(pt1,pt2) << endl;
}

int main() {
    func();
}