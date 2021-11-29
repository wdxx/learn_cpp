```c++
// 移动构造函数
#include <iostream>
#include <string.h>

class MyString {
public:
    // default constructor
    MyString(const char * initStr) {
        buffer = NULL;
        if (initStr != NULL) {
            buffer = new char[strlen(initStr) + 1];
            strcpy(buffer, initStr);
        }
        std::cout << "default constructor for buffer =" << static_cast<void * >(buffer) << '\n'; 
    }

    // copy constructor
    MyString(const MyString& copystr) {
        buffer = NULL;
        if (copystr.buffer != NULL) {
            buffer = new char[strlen(copystr.buffer) + 1];
            strcpy(buffer, copystr.buffer);
        }
        std::cout << "copy constructor for buffer =" << static_cast<void *>(buffer) << '\n';
    }

    // move constructor
    MyString(MyString&& str) {
        if (str.buffer != NULL) {
            buffer = str.buffer;
            str.buffer = NULL;
        }
        std::cout << "move constructor for buffer =" << static_cast<void *>(buffer) << '\n';
    }

    int GetLength() {
        return strlen(buffer);
    }

    const char * Get() {
        return buffer;
    }

    // destructor
    ~MyString() {
        std::cout << "destructor \n";
        if (buffer != NULL) {
            delete [] buffer;
        }
    }

private:
    char * buffer;
};

MyString Copy(MyString& str) {
    std::cout << "Copy Function\n";
    MyString copy(str);
    return copy;
}

int main(int argc, char ** argv) {
    MyString sayHello("Hello Word of c++");
    MyString otherSayHello(Copy(sayHello));

    return 0;
}
```
