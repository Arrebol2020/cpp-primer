## 练习 13.9
析构函数：用于销毁对象，由～后跟类名构成，没有返回值，也不带参数。在对象生命周期结束时，析构函数自动被调用
合成析构函数完成的工作：释放对象所占用的资源
什么时候会生成：当没有定义自己的析构函数时

## 练习 13.10
对于 StrBlob 对象销毁时，其合成析构函数会被调用，会将 shared_ptr 引用次数减1，如果为 0，则会释放内部的 vector 对象

对于 StrBlobStr 对象销毁时，其合成析构函数会被调用。`StrBlobStr` 中并没有动态分配内存或持有独立资源，因此合成析构函数将不会作特殊的资源清理工作

## 练习 13.11
``` c++
class HasPtr
{
public:
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) { }
    HasPtr& operator=(const HasPtr& rhs)
    {
        if (&rhs == this) return *this;    
        delete ps;

        ps = new std::string(*rhs.ps);
        i = rhs.i;

        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
}
```

## 练习 13.12
``` c++
bool fcn(const Sales_data* trans, Sales_data accum)
{
    Sales_data item1(*trans), item2(accum);
    return item1.isbn() != item2.isbn();
}
```
- 参数 `Sales_data accum`，在函数调用时，会调用`拷贝构造函数`；在函数结束时，会调用`析构函数`
- 在函数结束时，`item1` 变量会调用一次析构函数
- 在函数结束时，`item2` 变量会调用一次析构函数

## 练习 13.13
``` c++
#include <iostream>
#include <vector>

struct X
{
    X() { std::cout << "X()" << std::endl; }
    X(const X&) { std::cout << "X(const X&)" << std::endl; };
    X& operator=( const X&) { std::cout << "operator=(const X&)" << std::endl; return *this; }
    ~X() { std::cout << "~X()" << std::endl; }
};

void f1(X x) { std::cout << "value" << std::endl; };
void f2(X& x) { std::cout << "&" << std::endl; }

int main()
{
    X x;  // X()
    f1(x);  // X(const X&) value ~X()
    f2(x); // &

    X* ptr = new X(); //X()
    
    std::vector<X> v;
    v.push_back(x);  // X(const X&)
    std::cout << v.capacity() << std::endl;
    v.push_back(*ptr);  // X(const X&)
    std::cout << v.capacity() << std::endl;

    delete ptr;  // ~X()
    return 0;
}
// ~X()
```

- `X x;`：执行这行代码，将会输出 `X()`
- `f1(x);`：这行代码，函数参数是通过`值传递`，因此会调用拷贝构造函数，输出 `X(const X&)`，随后执行函数体，输出 `value`，最后当结束函数调用时，会调用析构函数，输出 `~X()`
- `f2(x);`：这行代码，函数参数是通过`引用传递`，执行函数体，输出 `&`
- `X* ptr = new X();`：这行代码，通过 new 操作符申请动态内存，会调用无参的构造函数，输出 `X()`
- `v.push_back(x);`：这行代码，push_back() 会调用`拷贝构造函数`，输出 `X(const X&)`
- `v.push_back(*ptr);`：这行代码，会输出
  ``` c++
  X(const X&)
  X(const X&)
  ~X()
  ```
  因为这里进行了扩容，会申请新的更大的一块内存，然后将原来的元素添加到新内存中，同时释放原元素
- `delete ptr;`：则会调用析构函数，输出 `~X()`
- 程序结束后，释放 v 中的元素和变量 x，输出3次 `~X()`