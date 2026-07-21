//
// Created by dayu on 2026/7/18.
//
#include <cstring>
#include <iostream>
using namespace std;
class Computer {
public:
    Computer(const char* brand,double price)
    :_brand(new char[strlen(brand)+1]())
    , _price(price) {
        strcpy(_brand,brand);
        cout<<"Computer constructor"<<endl;
    }

    ~Computer() {
        if (_brand) delete[] _brand;
        _brand = nullptr;
        cout << "Destructor called" << endl;
    }
private:
    char* _brand;
    double _price;
};

int main() {
    Computer pc("Apple",1222);
    Computer *pcPtr = new Computer("Apple",1222);
    delete pcPtr;
    pcPtr = nullptr;
}