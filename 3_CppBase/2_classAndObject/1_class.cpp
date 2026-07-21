//
// Created by dayu on 2026/7/17.
//
#include <cstring>
#include <iostream>
using namespace std;

class Computer {
    public:
    void setBrand(const char* brand) {
        strcpy(_brand, brand);
    }

    void setPrice(float price) {
        _price = price;
    }

    private:
    char* _brand;
    float _price;
};

int main(int argc, char *argv[]) {
    Computer computer;
    computer.setPrice(3.14);
}
