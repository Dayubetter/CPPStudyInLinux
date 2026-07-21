//
// Created by dayu on 2026/7/21.
//
#include <cstring>
#include<iostream>
using namespace std;

class Computer {
    public:

    static  Computer* getInstance() {
        if (_instance == nullptr) {
            _instance = new Computer();
        }
        return _instance;
    }

    void initComputer(const char* brand, int price) {
        // delete[] _brand;
        release(); // 修改
        _brand = new char[strlen(brand)+1];
        strcpy(_brand,brand);
        _price = price;
    }

    void destroy() {
        if (_instance != nullptr) {
            delete _instance;
            _instance = nullptr;
        }
    }

    private:
    Computer(const char * brand,int price) : _brand(new char[strlen(brand) + 1]()), _price(price) {
        strcpy(_brand,brand);
    }
    ~Computer() {
        release();
        //delete[] _brand;
        //_brand = nullptr;
    }
    void release() {
        if (_brand != nullptr) {
            delete[] _brand;
            _brand = nullptr;
        }
    }
    Computer(const Computer& c) = delete;
    Computer& operator=(const Computer& c) = delete;

    char * _brand;
    int _price;
    static Computer* _instance;
};
Computer* Computer::_instance = nullptr;

int main() {}