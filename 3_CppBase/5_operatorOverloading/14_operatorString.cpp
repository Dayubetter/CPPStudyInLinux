//
// Created by dayu on 2026/10/11.
//
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class String
{
public:
    String()
        // :_pstr(nullptr)
    :_pstr(new char[1]())
    {
        cout<<"String()"<<endl;
    }
    // String s1("hello");
    String(const char * pstr)
        :_pstr(new char[strlen(pstr) + 1]())
    {
        cout<<"String(const char *) "<<endl;
        strcpy(_pstr, pstr);
    }

    //  String  s2 = s1;
    String(const String & rhs)
        :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        cout<<"String(const String &) "<<endl;
        strcpy(_pstr, rhs._pstr);
    }

    ~String() {
        cout<<"~String()"<<endl;
        if (_pstr != nullptr) {
            delete[] _pstr;
            _pstr = nullptr;
        }
    }

    // String s1("hello");
    // String s2("world");
    // s1 = s1;
    // s1 = s2;
    String &operator=(const String &rhs) {
        cout<<"String &operator=(const String &) "<<endl;
        if (this != &rhs) {
            delete[] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1];
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }

    // s1 = "hello";
    String &operator=(const char * pstr) {
        cout<<"String &operator=(const char *) "<<endl;
        String tmp(pstr);
        *this = tmp;
        return *this;
    }

    //  s1 +=  s2;
    String &operator+=(const String &rhs) {
        cout<<"String &operator+=(const String &) "<<endl;
        char* temp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
        strcpy(temp, _pstr);
        strcat(temp, rhs._pstr); // 追加到末尾，覆盖‘\0’
        delete[] _pstr;
        _pstr = temp;
        return *this;
    }

    // s1 += "hello"
    String &operator+=(const char * pstr) {
        cout<<"String &operator+=(const char *) "<<endl;
        String tmp(pstr);
        *this += tmp;
        return *this;
    }

    // const String s1("hello");
    // s1[0]
    char &operator[](std::size_t index) // index >= 0
    {
        if (index < size()) {
            return _pstr[index];
        }else {
            static  char nullchar = '\0';
            return nullchar;
        }
    }

    const char &operator[](std::size_t index) const {
        if (index < size()) {
            return _pstr[index];
        }else {
            static char nullchar = '\0';
            return nullchar;
        }
    }

    std::size_t size() const {
        return strlen(_pstr);
    }

    const char* c_str() const {
        return _pstr;
    }

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char * _pstr;
};

bool operator==(const String &lhs, const String &rhs) {
    return !strcmp(lhs._pstr, rhs._pstr);
}

bool operator!=(const String &lhs, const String &rhs) {
    return strcmp(lhs._pstr, rhs._pstr);
}

bool operator<(const String &lhs, const String &rhs) {
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs) {
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String &lhs, const String &rhs) {
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String &lhs, const String &rhs) {
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

ostream &operator<<(ostream &os, const String &rhs) {
    if (rhs._pstr != nullptr) {
        os << rhs._pstr;
    }
    return os;
}

// String s1("hello");
// cin >> s1;
istream &operator>>(istream &is, String &rhs) {
    if (rhs._pstr != nullptr) {
        delete[] rhs._pstr;
        rhs._pstr = nullptr;
    }
    //  动态获取从键盘输入数据的长度
    vector<char> buffer;
    char ch;
    // while ((ch = is.get()) != '\n' && ch != ' '&& ch != '\t')
    while ((ch = is.get()) != '\n') {
        buffer.push_back(ch);
    }
    rhs._pstr = new char[buffer.size() + 1]();
    strncpy(rhs._pstr, &buffer[0], buffer.size());

    return is;
}

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

void test0() {
    string s1;
    string s2;
    cin >> s1 >> s2;
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
}

void test1() {
    String s1;
    String s2;
    cin >> s1 >> s2;
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
}

int main() {
    test1();
    return 0;
}