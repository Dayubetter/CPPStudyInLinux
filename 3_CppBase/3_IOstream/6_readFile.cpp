//
// Created by dayu on 2026/7/28.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void func() {
    ifstream ifile("3_output.cpp");
    long pos = ifile.tellg();
    cout << pos << endl;

    ifile.seekg(10);

    pos = ifile.tellg();
    cout << pos << endl;

    // string word;
    // ifile >> word;
    // cout << word << endl;

    char * buf = new char[100]();
    ifile.read(buf, 30);
    cout << buf << endl;

    delete [] buf;
    ifile.close();
}

int main(int argc, char *argv[]) {
    func();
}
