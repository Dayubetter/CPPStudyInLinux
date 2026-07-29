//
// Created by dayu on 2026/7/26.
//
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::istream;
using std::ifstream;
using std::string;

// 基类引用绑定派生类对象
void checkStatus(const istream& is) {
    cout << "is's goodbit:" << is.good() << endl;
    cout << "is's badbit:" << is.bad() << endl;
    cout << "is's eofbit:" << is.eof() << endl;
    cout << "is's failbit:" << is.fail() << endl;
}

void func() {
    // ifstream ifs("3_output.cpp");
    // ifstream ifs2 = "3_output.cpp";  被禁止了隐式转换 错误
    //
    // ifstream ifs;
    // ifs.open("3_output.cpp");

    // 文件输入流对象所绑定的文件要存在
    // 如果不存在，会使文件输入流对象的状态变为failbit
    // string filename("tt.cpp");
    string filename("3_output.cpp");
    ifstream ifile(filename);

    checkStatus(ifile);

    /*string word;
    ifile >> word;
    cout << word << endl;*/

    string word;
    // 输入流运算符以空格符、换行作为分隔符
    // ifs >> word 这个表达式的结果仍是ifs对象
    // 只要ifs对象是goodbit状态
    // 作判断时就可以自动转换成true
    while (ifile >> word) {
        cout << word << endl;
    }
    // 关闭文件流
    ifile.close();
}



int main(int argc, char *argv[]) {
    func();
}
