C++中可以通过构造函数进行隐式类型转换，例如可以将基本类型初始化对象。
```c++
#include <iostream>

class Human {
public:
    // 重载的构造函数，可以用于进行类型转换,这个转换通过编译器执行
    Human(int age) : mAge(age) {}
private:
    int mAge;
};

void PrintHuman(Human person) {
    std::cout << "Print nonthing \n";
}

int main(int argc, char ** argv) {
    // 这里进行了隐式转换
    Human person = 10;
    // 正常构造
    Human blackMan = Human(22);
  
    PrintHuman(person);
  
    // 这里进行了隐式转换
    PrintHuman(11);
    return 0;
}
```
某些情况下，使用隐式转换可能导致代码可读性变差，这种情况下可以使用关键字`explicit`来定义构造函数，避免隐式转换。
```c++
#include <iostream>

class Human {
public:
    explicit Human(int age) : mAge(age) {}
private:
    int mAge;
};

void PrintHuman(Human person) {
    std::cout << "Print nonthing \n";
}

int main(int argc, char ** argv) {
    // compile error: conversion from 'int' to non-scalar type 'Human' requested
    // Human person = 10;
    Human blackMan = Human(22);
    PrintHuman(blackMan);
  
    // compile error: could not convert '11' from 'int' to 'Human'
    // PrintHuman(11);
    return 0;
}
```
运算符函数也存在隐式转换的问题，也可以在运算符转换函数中使用`explicit`关键字禁止隐式转换。
