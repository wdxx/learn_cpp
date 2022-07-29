### 模板类
### 模板非类型参数
### 函数模板特化
### 类模板特化
### 类模板部分特化
### 针对指针的部分特化
### C++11 外部模板
参开：https://book.itheima.net/course/223/1275663370879508481/1275668314789519362
### 例子
```c++
#include <iostream>
#include <typeinfo>

// 一个特化的模板类的标志：在定义类实现时加上了<>，比如class A<int, T>；而在定义一个模板类的时候，class A后面是没有<>的




// trait 提供一种用来处理type属性的办法
// traits就是提取“被传进的对象”对应的返回类型

// 下面这个结构体可以通过is_void<T>::value来判断
// 类型T在编译期是否为void类型
template <typename T>
struct is_void {
    static const bool value = false;
};

// 模板特化
template <>
struct is_void<void> {
    static const bool value = true;
};

template <class I, class T>
void func_impl(I iter, T t) {
    T tmp;
    std::cout << "Type of tmp: " << typeid(tmp).name() << '\n';
    std::cout << "func proto: " << __PRETTY_FUNCTION__ << '\n';
}

template <class I>
void func(I iter) {
    // 这里传入的是 iter 以及 iter所指向的值
    func_impl(iter, *iter);
}

template <class T>
struct MyIter {
    // 定义了一个类型 value_type
    typedef T value_type;
    T* ptr;
    MyIter(T* p = nullptr) : ptr(p) {}
    T& operator* () const { return *ptr; }
};

template <class I>
// 申明 MyIter::value_type是一个类型，而不是一个成员变量
// funcC 返回类型为 I::value_type
typename I::value_type
funcC (I iter) {
    std::cout << "func proto: " << __PRETTY_FUNCTION__ << '\n';
    return *iter;
}

template <class I>
I
funcC (I* iter) {
    std::cout << "func proto: " << __PRETTY_FUNCTION__ << '\n';
    return *iter;
}

template <class I>
I
funcC (const I* iter) {
    std::cout << "func proto: " << __PRETTY_FUNCTION__ << '\n';
    return *iter;
}

template <class T>
struct Iter {
    typedef T value_type;
    T* ptr;
    Iter(T* ptr = nullptr) : ptr(nullptr) {}
    T& operator* () const { return *ptr; }
};

template <class T>
struct iterator_traits {
    // 这里定义类型
    typedef typename T::value_type value_type;
};

// 模板特化为指针
// 模板的特化，看最终使用时传入的类型
template <class T>
struct iterator_traits<T*> {
    typedef T value_type;
};

template <class T>
struct iterator_traits<const T*> {
    typedef T value_type;
};

// func 必须传入指针类型
template <class I>
typename iterator_traits<I>::value_type
funcFinal(I iter) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return *iter;
}

int main() {
    std::cout << is_void<int>::value << std::endl;
    std::cout << is_void<void>::value << std::endl;

    int i = 10;
    // func_impl 中  I: int*  T: int
    func(&i);

    MyIter<float> iter(new float(3.14));
    funcC(iter);

    int* p = &i;
    funcC(p);

    funcFinal(p);
    funcFinal(iter);

    return 0;
}
```
