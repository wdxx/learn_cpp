拷贝构造函数，编译器编译时，如果需要拷贝的情况下，会被调用，例如函数参数通过值传递，那么实参会被拷贝。
```c++
#include <iostream>
#include <string.h>

// best practice
// 类成员包含原始类型指针(*xxx)时，必须要实现
// 拷贝构造函数与复制赋值运算符
// 申明构造函数时，使用explicit修饰，避免隐式转换
class MyString {
public:
    // constructor
    MyString(const char *initString) {
        buffer = NULL;
        std::cout << "default construct \n";
        if (initString != NULL) {
            buffer = new char [strlen(initString) + 1];
            strcpy(buffer, initString);

            // 需要转换下指针，不然打印会有问题
            std::cout << "buffer points to " << std::hex << (unsigned int *)buffer << '\n';
        }
    }

    // copy constructor 由程序员提供
    // 当对象被复制时，由编译器调用
    MyString(const MyString & str) {
        buffer = NULL;
        std::cout << "Copy constructor: copy form MyString\n";
        if (str.buffer != NULL) {
            buffer = new char [strlen(str.buffer) + 1];
            strcpy(buffer, str.buffer);

            std::cout << "buffer points to " << std::hex << (unsigned int *)buffer << '\n';
        }
    }

    // destructor
    ~MyString() {
        std::cout << "Invoke MyString destructor\n";
        delete [] buffer;
    }

    int GetLength() {
        return strlen(buffer);
    }

    const char * Get() {
        return buffer;
    }

private:
    char *buffer;
};


void TestMyString(MyString str) {
    std::cout << "String buffer in MyString is " << str.GetLength() << " characters long\n";
    std::cout << "buffer contains: " << str.Get() << '\n';
    // 函数返回时会析构 str
}

int main(int argc, char ** argv) {
    MyString sayHello("Hello from String class");
    // sayHello 会被复制到 形参 str 里面,这个操作由编译器进行
    // 之所以复制是因为参数按值传递,所以buffer的值也被复制过去，但是
    // 其指向的内容并不会被复制
    TestMyString(sayHello);

    MyString ohterStr = sayHello;
    MyString ohterStr2 = sayHello;

    return 0;
}

```
