//
// Created by dayu on 2026/7/26.
//
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

void checkStatus(const istream& is, const ostream& os) {
    cout << "is's goodbit:" << is.good() << endl;
    cout << "is's badbit:" << is.bad() << endl;
    cout << "is's eofbit:" << is.eof() << endl;
    cout << "is's failbit:" << is.fail() << endl;
}

void  func() {
    checkStatus(cin, cout);
    int  num = 10;
    cin >> num;
    cout << "num:" << num << endl;
    checkStatus(cin, cout);

    if (!cin.good()) {
        cin.clear(); // 只恢复了流的状态，并没有清空缓冲区
        // 清空缓冲区
        // cin.ignore();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过坏输入
    }
    checkStatus(cin, cout);

    std::string line;
    cin >> line;
    cout << "line:" << line << endl;
    checkStatus(cin, cout);

    int num2 =34;
    cin >> num2;
    cout << "num2:" << num2 << endl;
    checkStatus(cin, cout);
}

int main(int argc, char *argv[]) {
    func();
}
