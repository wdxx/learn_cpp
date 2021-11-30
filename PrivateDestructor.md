将类的析构函数申明为`private`会导致不允许在栈上实例化类。
```c++
class MonsterDB {
public:
    MonsterDB() {}

private:
    ~MonsterDB();
};

int main(int argc, char ** argv) {
    MonsterDB db;
    return 0;
}
```
上面代码在编译的时候会报如下错误：
```
error: 'MonsterDB::~MonsterDB()' is private within this context
     MonsterDB db;
               ^~
```
这是因为对于c/c++编译器来说，针对栈内存的操作将由编译器来完成，比如进入函数前的入栈保存上下文操作，与函数返回时的出栈恢复操作。上面的例子中，当main函数返回时，c++编译会在返回前调用`Monster`的析构函数释放资源（因为db是在栈上申请的）。此时由于析构函数是`private`的导致不能访问而编译报错。
对于这种情况，应该在类中实现释放资源的方法。如果不实现将导致内存泄漏，看如下示例。
```c++
class MonsterDB {
public:
    MonsterDB() {}

private:
    ~MonsterDB();
};

int main(int argc, char ** argv) {
    MonsterDB* db = new MonsterDB();
    return 0;
}
```
上面的代码将导致内存泄漏。由于在main中不能调用析构函数，所以也不能调用`delete`。为了解决这个问题，需要在`Monster`类中添加一个公有静态成员函数。
```c++
class MonsterDB {
public:
    MonsterDB() {}

    static void Destroy(MonsterDB *pInstance) {
        delete pInstance;
    }

private:
    ~MonsterDB() {}
};

int main(int argc, char ** argv) {
    MonsterDB* db = new MonsterDB();
    MonsterDB::Destroy(db);
    return 0;
}
```
将析构函数申明为`private`主要用于防止实例在栈上创建，对于占用内存大的类，可以使用该方法。
