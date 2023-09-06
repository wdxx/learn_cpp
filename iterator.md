迭代器：迭代器能够使程序反复对STL容器内容进行访问。常见的的迭代器类别包括：输入、输出、前向、双向和随机访问。
容器可以比作一个数组，迭代器可以看作指向数组的指针，通过移动指针可以拿到数组里面的值。由于存放的类型不确定，容器与算法是通过迭代器关联到一起的，所以算法需要提取到迭代器指向的容器元素的类型。这个提取操作被封装为“萃取器”，traits。这个萃取器的功能就是从迭代器中提取除迭代器的value_type。
```c++
template<class IterT>
struct my_iterator_traits {
    typedef typename IterT::value_type value_type;
};
template<class IterT>
struct my_iterator_traits<IterT*> {
    typedef IterT value_type;
};
// my_iterator_traits::value_type 就是一个类型了
```
#### 输入迭代器
输入迭代器主要用于为程s序中的需要的数据源提供输入接口，数据源一般指容器、数据流等。输入迭代器只能从一个序列中读取数值，迭代器可以被修改、引用。比如用来读取文件。
#### 输出迭代器
输出迭代器主要用于输出程序中已经得到的数据结果（容器、数据流）。输出迭代器只能够向一个序列写入数据，输出迭代器可以被修改、引用。
#### 前向迭代器
前向迭代器被认为是输入和输出迭代器的组合。它为两者的功能提供支持。它允许访问和修改值。前向迭代器仅使用增量运算符 (++) 来遍历容器的所有元素。
#### 双向迭代器
双向迭代器既可以用来读又可以用来写。双向迭代器可以同时进行向前或者向后操作（++， --操作）。所有STL容器都提供了双向迭代器功能。
#### 随机迭代器
随机迭代器可以通过跳跃的方式访问容器中的任意数据。它具有双向迭代器的所有功能

#### 让自定义的类可以迭代
事实上要想进行迭代，一个类需要满足以下条件：
（1）拥有 begin 和 end 函数，返回值是一个可以自己定义的迭代器，分别指向第一个元素和最后一个元素。既可以是成员函数，也可以是非成员函数。
（2）迭代器本身支持 *、++、!= 运算符，既可以是成员函数，也可以是非成员函数。
```c++
#include <stdlib.h>
#include <iostream>  
using namespace std;

class IntVector {
	//迭代器类
	class Iter {
	public:
		Iter(IntVector* p_vec, int pos):_pos(pos),_p_vec(p_vec){}

		// these three methods form the basis of an iterator for use with range-based for loop  
		bool operator!= (const Iter& other) const
		{
			return _pos != other._pos;
		}

		// this method must be defined after the definition of IntVector,since it needs to use it  
		int& operator*() const
		{
			return _p_vec->get(_pos);
		}

		const Iter& operator++ ()
		{
			++_pos;
			return *this;
		}

	private:		
		IntVector *_p_vec;
		int _pos;
	};

public:
	IntVector(){}
	Iter begin(){
		return Iter(this,0);
	}
	Iter end(){
		return Iter(this, 20);
	}
	int& get(int col){
		return data[col];
	}
	void set(int index, int val){
		data[index] = val;
	}
private:
	int data[20] = {0};
};


int main(){
	IntVector v;
	for (int i = 0; i < 20; i++){
		v.set(i, i);
	}
	for (int& i : v) { i = i*i; cout << i <<" "; }
	system("pause");
}

```
输出： `0 1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361`
#### 参考
1. https://blog.csdn.net/lihao21/article/details/55043881
2. https://blog.csdn.net/K346K346/article/details/57403750
