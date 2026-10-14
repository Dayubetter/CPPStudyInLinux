//
// Created by dayu on 2026/10/13.
//

#ifndef __LINE_H__
#define __LINE_H__

//Line.h

// 内存布局：
// Line对象(栈上)
// └── _pimpl (指针8字节) ───> 堆上 LineImpl 对象
//                            ├─ Point _pt1
//                            └─ Point _pt2

class Line{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine() const;//打印Line对象的信息
private:
    class LineImpl;//类的前向声明
    LineImpl * _pimpl;
};
#endif //__LINE_H__
